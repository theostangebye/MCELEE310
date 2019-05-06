/* 
 * File:   cam_pid.h
 * Author: theostangebye
 *
 * Created on May 3, 2019, 1:02 PM
 */
#include "mcc_generated_files/mcc.h"

#ifndef CAM_PID_H
#define	CAM_PID_H

#ifdef	__cplusplus
extern "C" {
#endif

    /**
     * 
     * @param setpoint
     * @param pgain
     * @param dgain
     */
    void pid_init(uint8_t setpoint, float pgain, float dgain);
    
    /**
     * Generates a PID response based on finding the transition point from 
     * white to dark.  (inside border of outside lane marking).  
     * We compute the derivative of the pixel array and find the 
     * minimum derivative value.
     * The location of the minimum derivative value is the process value.
     * The error is setpoint - process value.
     * @param pixels
     * @return 
     */
    int8_t pid_getResponse(uint8_t* pixels);


#ifdef	__cplusplus
}
#endif

#endif	/* CAM_PID_H */

