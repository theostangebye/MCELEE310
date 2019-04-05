/* 
 * File:   ping.h
 * Author: theostangebye
 *
 * Created on April 4, 2019, 11:09 PM
 */

#ifndef PING_H
#define	PING_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    /**
     * Initialize Ping sensor.
     */
    void ping_init();
    
    /**
     * Measures distance to object
     * @return distance to object in inches.
     */
    float ping();


#ifdef	__cplusplus
}
#endif

#endif	/* PING_H */

