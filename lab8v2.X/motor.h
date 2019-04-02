/* 
 * File:   motor.h
 * Author: theostangebye
 *
 * Created on March 29, 2019, 10:59 PM
 */
#include "mcc_generated_files/mcc.h"

#ifndef MOTOR_H
#define	MOTOR_H

#ifdef	__cplusplus
extern "C" {
#endif

    void motor_init();
    void motor_set(uint8_t duty);

#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_H */

