/* 
 * File:   car_ctrl.h
 * Author: theostangebye
 *
 * Created on April 2, 2019, 4:02 PM
 */
#include "mcc_generated_files/mcc.h"

#ifndef CAR_CTRL_H
#define	CAR_CTRL_H

#ifdef	__cplusplus
extern "C" {
#endif

enum ctl_state_t {state_unset, state_high, state_vary, state_low}; // in h make these specific because they will be tied as aliases to integer values throughout entire program.

struct cam_t{
    bool read_ready;
    uint16_t cam_pixels[128];
    ctl_state_t status;
};

struct carctl_t {
	bool initialized;
	enum ctl_state_t state;
	uint16_t stateDuration;
	uint8_t throttleHighTime;
	uint8_t servoHighTime;
};

volatile struct carctl_t carctl; // declare it as volatile since both ISR and main will be using this object - this way the compiler will not try to optimize reads/writes to this object.

void carcontrol_init();

void carcontrol_ISR();

void carcontrol_steering(int8_t steering);

void carcontrol_throttle(uint8_t throttle);


#ifdef	__cplusplus
}
#endif

#endif	/* CAR_CTRL_H */

