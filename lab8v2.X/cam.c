#include "cam.h"
#include "mcc_generated_files/mcc.h"

/**
Black = GND
Red = VDD = 5v
Green = SI
White = AO
Brown = Clk

Exposure time of 2ms is referenced in data sheet, thus we will use TMR 6 with maximum prescaler and a 1:2 post scaler - giving us a maximum exposure of 4ms (based on fosc/4).
 */

// low level state of camera.
enum cam_line_state_t {ack_start, ack_started, read_clkIsHigh, read_clkIsLow, ack_end, ack_done};

volatile cam_t mycam;

volatile cam_line_state_t myline;

/**
 * This function will be used by the isr to be called every 2ms/128 secconds. 
 * It will read in the A0 line and uldate the clock line.
 */
/**
 * This function will be called every so often during the continous update
 * camera mode.  It will pulse SI and then load the TMR6 to interrupt a short 
 * time in the future in which case it will start enabling the AO_bit_ISR 
 * which will continously clock in lots of data from the camera.
 */
void AO_bit_ISR() {
    // if state is ack_start -> then we pulse SI High and move to ack_started
    // if state is ack_started -> pull SI low and move to read_clk_IsHigh, set clk high.
    // if state is read_clkIsHigh -> set clk high, increment counter. (as long as is < 128)
    // if state is read_clkIsLow -> set clk_High, then sample AO
    // if state is ack_end - pulse SI.
}


/**
 * Should Initializes Camera Hardware
 */
void cam_init() {
    // set clock and SI as outputs and latch them low
    // Enable ISR -> A0_bit_ISR() this ISR will trigger every 2ms/128 seconds
    // and will sample ADC if a ack is in progress.
}

/**
 * performs one single acquisition on the camera.
 */
void cam_start_single_shot() {
    // Set cam state to single mode (enum in H file.)
    // and then start ISR -> AO_bit_ISR.
}

/**
 * Will start the camera in such a way as to perform continuous acquisitions
 * through interrupts.
 */
void cam_start_continuous(){
    // set state to cam_state_continous
    // enable ISR. This isr will automaotically reload itself so that acks are 
    // performed continuously.
}

/**
 * If a continuous acquisition is going, this will stop it after allowing 
 * the system to complete its current acquisition.
 */
void cam_stop(){
    // set mode to cam_state_stopped
    // this should let the program finish its current ack and then stop.
}

/**
 * Get the latest 128 element vector representing the camera image.
 * @return returns a pointer to the 128 element, 16b valued vector
 * which is the latest camera observation
 * If the camera is not running, or a read is not ready - it will return 
 * 0
 */
uint16_t* cam_get(){
    // if read_ready is true - the return a pointer to the 128 element array
    // else return 0 as the pointer.
}
