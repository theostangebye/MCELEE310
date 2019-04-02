#include "car_ctrl.h"
#include "mcc_generated_files/mcc.h"

volatile struct carctl_t carctl;

void carcontrol_init() {
    carctl.initialized = true;
    carctl.state = state_unset;
    carctl.throttleHighTime = 0;
    carctl.servoHighTime = 0;
    // start PWM for both motor and servo
    
}

/**
 * Will be used as an interupt handler to update GPIO PWM vals
 */
void carcontrol_ISR();

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
