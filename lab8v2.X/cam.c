#include "cam.h"
#include "mcc_generated_files/mcc.h"

/**
Black = GND
Red = VDD = 5v
Green = SI
White = AO
Brown = Clk
 */

/** TIMING:
 * Set SI HIGH and then set clk HIGH, at this point, the cam will shift out a bit
 * Enable an interrupt to fire 4ms/128 /2 (for high time) seconds later.
 * 
 * This interrupt will first pull SI low pull clk low and will start an ADC value.  
 * It should also enable the ADC interrupt
 * 
 * Then this interrupt will read the ADC value and then set the CLK HIGH.  
 * This interrupt should also schedule the last interrupt (just above) to occur 
 * 4ms/128 /2 seconds later again.  It will also increment a counter (used for
 * array placement) and will then exit.
 * 
 * finally, once the counter reaches 127 (at which point we're at the end, we'll
 * finsih the ack by swapping arrays, etc.
 */

int timing_val = 0xff10;

// low level state of camera.
enum cam_line_state_t {CAM_START, CAM_IN_PROGRESS, CAM_DONE, CAM_UNSET};

struct cam_t{
    bool readFromFirst;
    uint8_t cam_pixels_1[128];
    uint8_t cam_pixels_2[128];
    enum cam_line_state_t status;
    int index;
};

volatile struct cam_t myCam;

void adc_ready_ISR();

/**
 * Stateful ISR for pulling clock low and starting ADC measurement.
 */
void timer_ISR() {
    TMR3_SetInterruptHandler(TMR3_DefaultInterruptHandler);// disable timer ISR.
    DEBUG_DIG_Toggle();

    if (myCam.status == CAM_START) {
        myCam.status = CAM_IN_PROGRESS;     // state = CAM_IN_PROGRESS.
        CAM_SI_SetLow();
        CAM_CLK_SetLow();
        TMR3_WriteTimer(timing_val);            // Load for 15us interrupt
        TMR3_SetInterruptHandler(timer_ISR); // Re-enable ISR
        TMR3_StartTimer();
    } else if (myCam.status == CAM_IN_PROGRESS) {
        CAM_CLK_SetHigh();               // Set CLK LOW
        PIE1bits.ADIE = 1;              // enable adc interrupt
        ADCON0bits.GO = 1;                  // Start Conversion.         
    }
}

/**
 * Will be used for setting clk high and reading from ADC
 */
void adc_ready_ISR() {
    PIE1bits.ADIE = 0;              // disable adc interrupt    
    DEBUG_DIG_Toggle();
    if (myCam.readFromFirst) {
        // read from ADC place val in array
        myCam.cam_pixels_2[myCam.index] = ADRESH;
    } else {
        myCam.cam_pixels_1[myCam.index] = ADRESH;
    }
    myCam.index++;  // increment index
    
    if (myCam.index >= 128) {
        // we're done with this ack
        // if index < 127 -> increment index & setup timer ISR.
        // else set state to CAM_DONE.
        myCam.status = CAM_DONE;
        CAM_CLK_SetLow();                   // CLK -> HIGH
        CAM_SI_SetLow();                    // CLK -> HIGH


    } else {
        CAM_CLK_SetLow(); 
        TMR3_SetInterruptHandler(timer_ISR);
        TMR3_WriteTimer(timing_val);            // Load for 15us interrupt
        TMR3_StartTimer();
    }
}

/**
 * Should Initializes Camera Hardware
 */
void cam_init() {
    CAM_SI_SetLow();            // set SI low
    CAM_CLK_SetLow();           // set cam_clk low
    CAM_SI_SetDigitalOutput();
    CAM_CLK_SetDigitalOutput();
    ADCC_SetInterruptHandler(adc_ready_ISR); // setup ADC interrupt
    ADCC_SelectChannel(CAM_A0,2);
    
    
    
    
    myCam.index = 0;            // index = 0;
    myCam.status = CAM_DONE;    // state = CAM_DONE.
    
    ///////////////// Following from Page 547 of datasheet \\\\\\\\\\\\\\\\\\\\\
    
//    ADCON0bits.ADFM = 0;    // Left Justify ADCON0bits.CS = 1; 
//    ADCON0bits.ADCS = 1;    // FRC Clock
//    ADCON0bits.ADON = 1;    // ADC ON
}

/**
 * Will start the camera in such a way as to perform continuous acquisitions
 * through interrupts.
 */
void cam_start() {
    // If state == CAM_DONE -> then we can start, otherwise dont.
    if (myCam.status == CAM_DONE){
        myCam.status = CAM_START;           // state = cam_START

        myCam.index = 0;                    // index = 0;
        myCam.readFromFirst = !myCam.readFromFirst; // swap arrays
        CAM_SI_SetHigh();                   // SI -> HIGH
        __delay_us(3);
        CAM_CLK_SetHigh();                  // CLK -> HIGH
        TMR3_SetInterruptHandler(timer_ISR);// set up timer interrupt
        TMR3_WriteTimer(timing_val);            // Load for 15us interrupt
        TMR3_StartTimer();
        ADCON0bits.ADON = 1;                // ADC ON
        PIE1bits.ADIE = 0;              // disable adc interrupt
    }
}

/**
 * If a continuous acquisition is going, this will stop it after allowing 
 * the system to complete its current acquisition.
 */
void cam_stop() {

}

/**
 * Get the latest 128 element vector representing the camera image.
 * @return returns a pointer to the 128 element, 16b valued vector
 * which is the latest camera observation
 * If the camera is not running, or a read is not ready - it will return 
 * an array with a 0 as the first element.
 */
void cam_get(uint16_t* pixels) {
    if (myCam.readFromFirst) {
        for (int i = 0; i < 128; i++){
            pixels[i] = myCam.cam_pixels_1[i];
        }
    } else {
        for (int i = 0; i < 128; i++){
            pixels[i] = myCam.cam_pixels_2[i];
        }
    }
}