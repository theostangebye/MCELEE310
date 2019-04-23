#include "cam.h"
#include "mcc_generated_files/mcc.h"

/**
Black = GND
Red = VDD = 5v
Green = SI
White = AO
Brown = Clk
 * /

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

// low level state of camera.
enum cam_line_state_t {CAM_START, CAM_IN_PROGRESS, CAM_DONE, CAM_UNSET};

struct cam_t{
    bool readFromFirst;
    uint16_t cam_pixels_1[128];
    uint16_t cam_pixels_2[128];
    enum cam_line_state_t status;
    int index;
};

volatile struct cam_t myCam;

/**
 * Stateful ISR for pulling clock low and starting ADC measurement.
 */
void timer_ISR() {
    // disable timer ISR.
    // if state = CAM_IN_PROGRESS
    // Set CLK LOW
    // Start ADC
}

/**
 * Will be used for setting clk high and reading from ADC
 */
void adc_ready_ISR() {
    // read from ADC
    // place val in array
    // increment index
    // if index < 127 -> increment index & setup timer ISR.
    // else set state to CAM_DONE.
}

/**
 * Should Initializes Camera Hardware
 */
void cam_init() {
    // set SI low
    // set cam_clk low
    // index = 0;
    // state = CAM_UNSET.
}

/**
 * Will start the camera in such a way as to perform continuous acquisitions
 * through interrupts.
 */
void cam_start() {
    // If state == CAM_UNSET -> then we can start, otherwise dont.
        // state = cam_START
        // set up timer interrupt
        // setup ADC interrupt
        // index = 0;
        // swap arrays
        // SI -> HIGH
        // CLK -> HIGH
        // state = CAM_IN_PROGRESS.
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
uint8_t* cam_get() {
    if (readFromFirst) {
        return &myCam.cam_pixels_1;
    } else {
        return &myCam.cam_pixels_2;
    }
}