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
     * Begins a Ping measurement
     */
    void ping_send();

    /**
     * Will return the latest ping measurement.
     * If a reading is not ready - it will return 0.
     * @return distance in CM to nearest object.
     */
    float ping_get();

#ifdef	__cplusplus
}
#endif

#endif	/* PING_H */

