#include "mcc_generated_files/mcc.h"

uint8_t center_val;
uint8_t range_val;

 // min is 31, max is 51, but 40 looks middle

/**
 * 
 * @param center Typicaly 40.  It is the PWM val to drive straight.
 * @param range  center ± range gives min/max pwm vals. Typically 10.
 */
void servo_init(uint8_t center, uint8_t range){
    center_val = center;
    range_val = range;
    PWM4_LoadDutyValue(center_val);

}

/**
 * Moves the steering servo to a steering position
 * @param pos a [-1,1] float representing steering angle
 */
void servo_set(double pos){
    uint8_t new_val = (range_val*pos) + center_val;
    PWM4_LoadDutyValue(new_val);
}
