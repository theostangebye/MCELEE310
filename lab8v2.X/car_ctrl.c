#include "car_ctrl.h"
#include "mcc_generated_files/mcc.h"

/**
 * We are reconstructing the pulse coded output necessary for servo motors
 * 
 * Period:  |<---------------- PERIOD ---------------->|<---------- ....
 * pin dig: |  out HIGH  | out varies | out always LOW |  out HIGH  ....
 * pin out: -------------\============\________________/----------- ....
 * state:   | state_high | state_vary |   state_low    | state_high ....
 * time:    0ms          1ms          2ms    ....      20ms         ....
 */

volatile struct carctl_t carctl;

/**
stateTime will be used to keep track of the time spent in the current state
 */
int stateTime; // [10 uS]

void carcontrol_init() {
    carctl.initialized = true;
    carctl.state = state_unset;
    carctl.throttleHighTime = 0;
    carctl.servoHighTime = 0;
    // Set new ISR handler function
    TMR2_SetInterruptHandler(carcontrol_ISR);   
    stateTime = 0;
}

/**
 * Will be used as an interupt handler to update GPIO PWM vals
 */
void carcontrol_ISR(){
    // states are: state_unset, state_high, state_vary, state_low}
    switch (carctl.state) {
        case state_unset:
            // set state to high
            carctl.state = state_high;
            IO_RA0_SetHigh();
            stateTime = 0;
        break; /* optional */
        case state_high:
            stateTime++;
            IO_RA0_SetHigh();
            if (stateTime >= 100) {
                // time for next state
                carctl.state = state_vary;
                stateTime = 0;
            }
        break;
        case state_vary:
            stateTime++;
            if (stateTime > carctl.throttleHighTime) {
                IO_RA0_SetLow();
            }
            if (stateTime >= 100) {
                carctl.state = state_low;
                stateTime = 0;
            }
        break;
        case state_low:
            stateTime++;
            IO_RA0_SetLow();
            if (stateTime >= 1800) {
                carctl.state = state_high;
                stateTime = 0;
                IO_RA0_SetHigh();
            }
        break;
    }
}

/**
 * Updates servo position that will be driven to the servo 
 * during the next ISR.
 * @param steering a [-50 to 50] value where 0 is center
 */
void carcontrol_steering(int8_t steering) {
    /**
     * throttleHighTime is in uS.  as such, it will range from 0 to 1000.
     * we will be running the ISR every 10 uS and so we this will give us
     * an output resolution of 100 different values (1000 uS / 10 uS = 100)
     * 
     *      steering =   0 -> hightime =  50
     *      steering =  50 -> hightime = 100
     *      steering = -50 -> hightime =   0
     */
    
    // coerce values before translation.
    if (steering < -50) steering = -50;
    if (steering >  50) steering =  50;
    
    carctl.servoHighTime = steering + 50;
}

/**
 * Updates the motor speed which will be set during the ISR routine
 * @param throttle a [0,100] value specifying motor speed.
 */
void carcontrol_throttle(uint8_t throttle) {
    // coerce values before translation.
    if (throttle >  100) throttle =  100;
    carctl.throttleHighTime = throttle;
}
