#include "mcc_generated_files/mcc.h"

/* 
 * File:   cam.h
 * Author: theostangebye
 *
 * Created on April 16, 2019, 1:21 PM
 */

#ifndef CAM_H
#define	CAM_H

#ifdef	__cplusplus
extern "C" {
#endif

/**
 * Should Initializes Camera Hardware
 */
void cam_init();

/**
 * Will start the camera in such a way as to perform continuous acquisitions
 * through interrupts.
 */
void cam_start();

/**
 * If a continuous acquisition is going, this will stop it after allowing 
 * the system to complete its current acquisition.
 */
void cam_stop();

/**
 * Get the latest 128 element vector representing the camera image.
 * @return returns a pointer to the 128 element, 16b valued vector
 * which is the latest camera observation
 * If the camera is not running, or a read is not ready - it will return 
 * an array with a 0 as the first element.
 */
void cam_get(uint8_t* copyHere);
    
#ifdef	__cplusplus
}
#endif

#endif	/* CAM_H */

