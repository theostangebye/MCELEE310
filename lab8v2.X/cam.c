#include "cam.h"
#include "mcc_generated_files/mcc.h"

/**
Black = GND
Red = VDD = 5v
Green = SI
White = AO
Brown = Clk
*/

/**
 *  TIMING:
 * Set SI HIGH and then set clk HIGH, at this point, the cam will shift out a bit
 * Enable an interrupt to fire 4ms / 128 / 2
 *  (for high time) seconds later.
 * 
 * This interrupt will first pull SI low pull clk low and will start an ADC value.  
 * It should also enable the ADC interrupt
 * 
 * Then this interrupt will read the ADC value and then set the CLK HIGH.  
 * This interrupt should also schedule the last interrupt (just above) to occur 
 * 4ms 128 2 seconds later again.  It will also increment a counter (used for
 * array placement) and will then exit.
 * 
 * finally, once the counter reaches 127 (at which point we're at the end, we'll
 * finsih the ack by swapping arrays, etc.
 */

struct cam_t{
    bool readFromFirst;
    uint8_t cam_pixels_1[128];
    uint8_t cam_pixels_2[128];
    enum cam_state_t {CAM_START, CAM_IN_PROGRESS, CAM_DONE, CAM_UNSET} status;
    int index;
};

volatile struct cam_t myCam;

/**
 * Stateful ISR for pulling clock low and starting ADC measurement.
 */
void timer_ISR() {
    TMR3_SetInterruptHandler(TMR3_DefaultInterruptHandler);// disable timer ISR.
    if (myCam.status == CAM_START) {
        myCam.status = CAM_IN_PROGRESS;     // state = CAM_IN_PROGRESS.
        CAM_SI_SetLow();
        CAM_CLK_SetLow();
        ADCON0bits.ADON = 1;                // ADC ON
        TMR3_WriteTimer(0xff10);            // Load for 15us interrupt
        TMR3_StartTimer();
    } else if (myCam.status == CAM_IN_PROGRESS) {
        CAM_CLK_SetLow();               // Set CLK LOW
        ADCC_StartConversion(CAM_AO);   // Start ADC
    }
 
}

/**
 * Will be used for setting clk high and reading from ADC
 */
void adc_ready_ISR() {
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
        ADCON0bits.ADON = 0;    // ADC ON
    } else {
        TMR3_WriteTimer(0xff10);            // Load for 15us interrupt
        TMR3_SetInterruptHandler(timer_ISR);
        TMR3_StartTimer();
        CAM_CLK_SetHigh(); 
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
    ADCC_SetADIInterruptHandler(adc_ready_ISR);
    

    myCam.index = 0;            // index = 0;
    myCam.status = CAM_DONE;    // state = CAM_DONE.
//    ADCC_Initialize();          // ADC INIT
    
    ///////////////// Following from Page 547 of datasheet \\\\\\\\\\\\\\\\\\\\\
    
    ADCON0bits.ADFM = 1;    // right justify ADCON0bits.CS = 1; 
    ADCON0bits.ADCS = 1;    // FRC Clock
    ADCON0bits.ADON = 1;    // ADC ON
}

/**
 * Will start the camera in such a way as to perform continuous acquisitions
 * through interrupts.
 */
void cam_start() {
    // If state == CAM_DONE -> then we can start, otherwise dont.
    if (myCam.status == CAM_DONE){
        myCam.status = CAM_START;           // state = cam_START
        TMR3_SetInterruptHandler(timer_ISR);// set up timer interrupt
        TMR3_WriteTimer(0xff10);            // Load for 15us interrupt
        TMR3_StartTimer();
        ADCC_SetADIInterruptHandler(adc_ready_ISR); // setup ADC interrupt
        ADCON0bits.GO = 1;                  // Start Conversion.
        myCam.index = 0;                    // index = 0;
        myCam.readFromFirst = !myCam.readFromFirst; // swap arrays
        CAM_SI_SetHigh();                   // SI -> HIGH
        CAM_CLK_SetHigh();                  // CLK -> HIGH
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
void cam_get(uint8_t* copyHere) {
    if (myCam.readFromFirst) {
        for (int i = 0; i < 128; i++){
            copyHere[i] = myCam.cam_pixels_1[i];
        }
    } else {
        for (int i = 0; i < 128; i++){
            copyHere[i] = myCam.cam_pixels_2[i];
        }
    }
}