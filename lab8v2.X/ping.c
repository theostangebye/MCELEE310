#include "mcc_generated_files/mcc.h"

/**
 * 
 * TMR1 is used for ISRs related to the ping module.
 * 
 * This struct is internal to this class and holds information related to our
 * latest ping measurement
 */
struct ping_stat_t {
    bool readReady;    // whether or not a distance calc is ready.
    bool pingInAir;   // true when a ping is sent, false when it is recieved.
    float measurment;   // distance in [cm]
    bool pingStarted;
};

volatile struct ping_stat_t status;

/**
 * Interrupt will enable and start off CCP1.
 */
void ping_RC2_went_HIGH() {
    IOCCF2_SetInterruptHandler(IOCCF2_DefaultInterruptHandler); // disable IOC
    
    TMR1_WriteTimer(0); // Reset timer (in case ping doesn't respond)
    PIE6bits.CCP1IE = 1;// Enable CCP
    TMR1_StartTimer();  // Start timer
}

/**
 * During a measuremnt, this will be called after 20 ms and can be useful in the
 * event that we don't get a signature back from PING
 * 
 * Otherwise, we'll use this as a way to conduct our initial 2us pulse for the 
 * ping module.
 */
void ping_TMR1Overflow_isr() { 
    if (status.pingInAir) {
        // we've waited on ping too long and need to break/Reset or something
        // TODO -> basically reset for another ping.
    } else {
        // if a ping isn't in the air, set GPIO as input
        RC2_SetLow();          // latch val
        RC2_SetDigitalInput(); // set pin as GPIO input
        
        // enable interrupt on Pin change (which will wait for Ping to respond)
        IOCCF2_SetInterruptHandler(ping_RC2_went_HIGH); // enable IOC
        status.pingInAir = true; // a ping should be in the air soon!
    }
}

/**
 * Used as the call back function for the CCP1 overflow.
 * @param number of system clocks ping was in air.
 */
void ping_CCP1_triggered(uint16_t timeOfFlight) {
    // finish calc -> reset pingStarted and get ready to return!
    TMR1_StopTimer(); // keep timer from overflowing
    
    status.measurment = 0.0000214375 * (float) timeOfFlight;
    
    PIE6bits.CCP1IE = 0;    // disable CCP1 until ping is in air
    status.pingInAir = false;
    status.pingStarted = false;
    status.readReady = true;
}

/**
 * Initialize Ping sensor.
 */
void ping_init() {
    static bool initialized = false;
    CCP1_SetCallBack(ping_CCP1_triggered);  // set callback function.
    PIE6bits.CCP1IE = 0;                    // disable CCP1 until ping is in air
    TMR1_SetInterruptHandler(ping_TMR1Overflow_isr); // set timer ISR
    IOCCF2_SetInterruptHandler(IOCCF2_DefaultInterruptHandler); // dummy isr.
    status.readReady = false;
    status.pingInAir = false;
    status.pingStarted = false;
    initialized = true;
}
    
/**
 * Measures distance to object
 * @return distance to object in inches.
 */
void ping_send() {
    
    ping_init();
    
    if (!status.pingStarted){

        PIE6bits.CCP1IE = 0;    // disable CCP1 until ping is in air

        TMR1_WriteTimer(0xFFFC);// load for 2us timer
        RC2_SetHigh();          // latch val
        RC2_SetDigitalOutput(); // set pin as GPIO output
        TMR1_StartTimer();      // Start timer
        status.pingStarted = true;
    }

}

/**
 * Will return the latest ping measurement.
 * If a reading is not ready - it will return 0.
 * @return distance in CM to nearest object.
 */
float ping_get() {
    if (status.readReady) {
        return status.measurment;
    } else {
        return 0;
    }
}
