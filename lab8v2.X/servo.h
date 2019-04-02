/* 
 * File:   servo.h
 * Author: theostangebye
 *
 * Created on April 1, 2019, 11:19 PM
 */
#include "mcc_generated_files/mcc.h"

#ifndef SERVO_H
#define	SERVO_H

#ifdef	__cplusplus
extern "C" {
#endif

    void servo_init(uint8_t center, uint8_t range);
    void servo_set(double pos);


#ifdef	__cplusplus
}
#endif

#endif	/* SERVO_H */

