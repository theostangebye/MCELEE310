#include "mcc_generated_files/mcc.h"

/**
 * This struct is internal to this class and holds information related to our
 * latest ping measurement
 */
struct ping_stat_t {
    bool read_ready;
    float measurment;
};

void ping_isr() {

}

/**
 * Initialize Ping sensor.
 */
void ping_init() {
    static bool initialized = false;
    
    
    initialized = true;
}
    
/**
 * Measures distance to object
 * @return distance to object in inches.
 */
void ping_send() {

}

/**
 * Will return the latest ping measurement.
 * If a reading is not ready - it will return 0.
 * @return distance in CM to nearest object.
 */
float ping_get();
