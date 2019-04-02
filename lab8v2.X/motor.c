#include "motor.h"
#include "mcc_generated_files/mcc.h"

/**
 * Sets Duty Cycle on Motor
 * @param duty Speed percentage (0% to 100%)
 */
void set_motor_duty(unsigned char duty) {
    // min duty cycle is 30 and mas is 61.
    int duty_val = (((double) duty)/100) * 30 + 31;
    PWM3_LoadDutyValue(duty_val);

}
