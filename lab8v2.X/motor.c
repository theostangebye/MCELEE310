#include "motor.h"
#include "mcc_generated_files/mcc.h"

uint8_t max;

/**
 * Sets up the motor
 */
void motor_init(uint8_t max_duty) {
    motor_set(0); // start sending PWM
    max = max_duty;
}

/**
 * Sets Duty Cycle on Motor
 * @param duty Speed percentage (0% to 100%)
 */
void motor_set(uint8_t duty) {
    if (duty > max) duty = max;
    // min duty cycle is 30 and mas is 61.
    int duty_val = (((double) duty)/100) * 30 + 31;
    PWM3_LoadDutyValue(duty_val);
}
