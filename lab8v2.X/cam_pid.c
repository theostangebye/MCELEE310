#include "mcc_generated_files/mcc.h"
#include "cam_pid.h"

uint8_t sp;
uint8_t last_error;
float pg;
float dg;

void pid_init(uint8_t setpoint, float pgain, float dgain) {
    sp = setpoint;
    pg = pgain;
    dg = dgain;
    last_error = 0;
}

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
int8_t pid_getResponse(uint8_t* pixels) {
    
    /**
     * Search for boarder in cam array. 
     */
    int16_t der_min = 0;
    uint8_t der_min_loc = 0;
    int16_t der = 0;
    for (int i = 0; i < 126; i++) {
        der = pixels[i+1] - pixels[i]; // compute derivative of pixel value
        if (der < der_min) {
            // we have a new minimum derivative value 
            // the greatest minimum derivative should be where the track goes 
            // from white to black.
            der_min = der;
            der_min_loc = i;
        }
    }
    // PID Calculations
    uint8_t error = sp - der_min_loc;       // Compute error (setpoint - pv)
    int16_t der_error = error - last_error; // compute derivative of error
    
    last_error = error;
    
    return (int8_t) pg*error + dg * der_error; // compute pid response
}

/**
 Negative Value -> pv is > sp.
 Positive Value -> pv is < sp.
 */
