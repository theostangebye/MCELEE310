#include "mcc_generated_files/mcc.h"

volatile bool read_ready;
volatile uint16_t  time_val;

void ping_isr() {
    
    if (IO_RA2_GetValue()) {
        // pin is high -> start stopwatch
        TMR3_WriteTimer(0);     // clear timer
        TMR3_StartTimer();  // start timer
    } else {
        // pin is low  -> read  stopwatch
        TMR3_StopTimer();
        time_val = TMR3_ReadTimer();
        read_ready = true;
    }

}

/**
 * Initialize Ping sensor.
 */
void ping_init() {
    IOCAF2_SetInterruptHandler(ping_isr);
    TMR3_Initialize();

    read_ready = false;
    time_val = 0;

}
    
/**
 * Measures distance to object
 * @return distance to object in inches.
 */
float ping() {
    // wait for a sentinel value.
    IO_RA2_SetLow();            // Latch val
    IO_RA2_SetDigitalOutput();  // Set output
    __delay_us(2);
    IO_RA2_SetHigh();   // signal to ping for 10 us
    __delay_us(10);
    
    IO_RA2_SetLow();    // Switch to input
    IO_RA2_SetDigitalInput();
    
    while (! read_ready) {
        // wait for reading to happen
    }
    
    // TODO: compute time value based on time_val;
    
    read_ready = false; // for next time.
    
    float distance = 0.0000214375 * (float) time_val;
    
    return distance;
}