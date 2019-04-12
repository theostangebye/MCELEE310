#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/ccp1.h"

/**
 * 
 * TMR1 is used for ISRs related to the ping module.
 * 
 * This struct is internal to this class and holds information related to our
 * latest ping measurement
 */
struct ping_stat_t {
    bool readReady;    // whether or not a distance calc is ready.
    double measurment;   // distance in [cm]
    bool pingStarted;
    uint16_t tof;
};

void ping_RC2_went_HIGH();

volatile struct ping_stat_t status;

/**
 * We found out that the MCC generated code for TMR1 actually starts timer 1
 * after loading it.  To fix this, I've copied the MCC code below and removde 
 * the portion which starts timer 1.
 * @param timerVal
 */
void TMR1_WriteTimer_NoStart(uint16_t timerVal)
{
    if (T1CONbits.nT1SYNC == 1)
    {
        // Stop the Timer by writing to TMRxON bit
        T1CONbits.TMR1ON = 0;

        // Write to the Timer1 register
        TMR1H = (timerVal >> 8);
        TMR1L = timerVal;
    }
    else
    {
        // Write to the Timer1 register
        TMR1H = (timerVal >> 8);
        TMR1L = timerVal;
    }
}

/**
 * During a measurement, this will be called after 20ms and can be useful in the
 * event that we don't get a signature back from PING
 * 
 * Otherwise, we'll use this as a way to conduct our initial 2us pulse for the 
 * ping module.
 */
void ping_TMR1Overflow_isr() { 
    TMR1_SetInterruptHandler(TMR1_DefaultInterruptHandler); // disable timer interrupt
    RC2_SetLow();          // latch val
    RC2_SetDigitalInput(); // set pin as GPIO input
    
    // enable interrupt on Pin change (which will wait for Ping to respond)
    IOCCF2_SetInterruptHandler(ping_RC2_went_HIGH); // enable IOC
}

/**
 * Interrupt will enable and start off CCP1.
 */
void ping_RC2_went_HIGH() {
    IOCCF2_SetInterruptHandler(IOCCF2_DefaultInterruptHandler); // disable IOC
    TMR1_SetInterruptHandler(TMR1_DefaultInterruptHandler); // disable timer interrupt

    TMR1_WriteTimer(0); // Reset timer (in case ping doesn't respond)
    TMR1_StartTimer();
    DEBUG_Scope_SetHigh();
    PIE6bits.CCP1IE = 1;    // enable CCP1
    

}

/**
 * Used as the call back function for the CCP1 overflow.
 * @param number of system clocks ping was in air.
 */
void ping_CCP1_triggered(uint16_t timeOfFlight) {
    status.tof = timeOfFlight;
    status.pingStarted = false;
    status.readReady = true;
//    DEBUG_DIG_SetLow();
    PIE6bits.CCP1IE = 0;    // disable CCP1
    DEBUG_Scope_SetLow();
}

/**
 * Initialize Ping sensor.
 */
void ping_init() {
    DEBUG_DIG_SetHigh();
    status.readReady = false;
    status.pingStarted = false;
    PIE6bits.CCP1IE = 0; // disable CCP1 temporarily.
    TMR1_SetInterruptHandler(TMR1_DefaultInterruptHandler);     // dummy isr
    IOCCF2_SetInterruptHandler(IOCCF2_DefaultInterruptHandler); // dummy isr.
    CCP1_SetCallBack(ping_CCP1_triggered);  // set callback function.
    DEBUG_DIG_SetLow();
}
    
/**
 * Measures distance to object
 * @return distance to object in inches.
 */
void ping_send() {
    __delay_us(10);
    if (!status.pingStarted) {
        RC2_SetHigh();          // latch val
        RC2_SetDigitalOutput(); // set pin as GPIO output
        TMR1_SetInterruptHandler(ping_TMR1Overflow_isr); // enable interrupt
        TMR1_WriteTimer(0xFFFC);// load for 2us timer
        TMR1_StartTimer();      // Start timer
//        status.pingStarted = true;
    }
}

/**
 * Will return the latest ping measurement.
 * If a reading is not ready - it will return 0.
 * @return distance in CM to nearest object.
 */
float ping_get() {
    if (status.readReady) {
        status.readReady = false;
        return status.measurment;
    } else {
        return 0;
    }
}
