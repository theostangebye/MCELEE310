#include "motor.h"
#include "mcc_generated_files/mcc.h"

/**
 * Sets up the motor
 */
void motor_init() {
    motor_set(0); // start sending PWM
}

/**
 * Sets Duty Cycle on Motor
 * @param duty Speed percentage (0% to 100%)
 */
void motor_set(uint8_t duty) {
    // min duty cycle is 30 and mas is 61.
    int duty_val = (((double) duty)/100) * 30 + 31;
    PWM3_LoadDutyValue(duty_val);
}
