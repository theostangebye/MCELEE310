/* 
 * File:   cam_pid.h
 * Author: theostangebye
 *
 * Created on May 3, 2019, 1:02 PM
 */

#ifndef CAM_PID_H
#define	CAM_PID_H

#ifdef	__cplusplus
extern "C" {
#endif

    pid_init();
    
    int_8t pid_getResponse(uint8_t* pixels);


#ifdef	__cplusplus
}
#endif

#endif	/* CAM_PID_H */

