/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC18F25Q10
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.00
        MPLAB 	          :  MPLAB X 5.10	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set THROTTLE aliases
#define THROTTLE_TRIS                 TRISAbits.TRISA0
#define THROTTLE_LAT                  LATAbits.LATA0
#define THROTTLE_PORT                 PORTAbits.RA0
#define THROTTLE_WPU                  WPUAbits.WPUA0
#define THROTTLE_OD                   ODCONAbits.ODCA0
#define THROTTLE_ANS                  ANSELAbits.ANSELA0
#define THROTTLE_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define THROTTLE_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define THROTTLE_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define THROTTLE_GetValue()           PORTAbits.RA0
#define THROTTLE_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define THROTTLE_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define THROTTLE_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define THROTTLE_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define THROTTLE_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define THROTTLE_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define THROTTLE_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define THROTTLE_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set STEERING aliases
#define STEERING_TRIS                 TRISAbits.TRISA1
#define STEERING_LAT                  LATAbits.LATA1
#define STEERING_PORT                 PORTAbits.RA1
#define STEERING_WPU                  WPUAbits.WPUA1
#define STEERING_OD                   ODCONAbits.ODCA1
#define STEERING_ANS                  ANSELAbits.ANSELA1
#define STEERING_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define STEERING_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define STEERING_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define STEERING_GetValue()           PORTAbits.RA1
#define STEERING_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define STEERING_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define STEERING_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define STEERING_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define STEERING_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define STEERING_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define STEERING_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define STEERING_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set RC2 procedures
#define RC2_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define RC2_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define RC2_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define RC2_GetValue()              PORTCbits.RC2
#define RC2_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define RC2_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define RC2_SetPullup()             do { WPUCbits.WPUC2 = 1; } while(0)
#define RC2_ResetPullup()           do { WPUCbits.WPUC2 = 0; } while(0)
#define RC2_SetAnalogMode()         do { ANSELCbits.ANSELC2 = 1; } while(0)
#define RC2_SetDigitalMode()        do { ANSELCbits.ANSELC2 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCCF2 pin functionality
 * @Example
    IOCCF2_ISR();
 */
void IOCCF2_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCCF2 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCCF2 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF2_SetInterruptHandler(MyInterruptHandler);

*/
void IOCCF2_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCCF2 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCCF2_SetInterruptHandler() method.
    This handler is called every time the IOCCF2 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF2_SetInterruptHandler(IOCCF2_InterruptHandler);

*/
extern void (*IOCCF2_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCCF2 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCCF2_SetInterruptHandler() method.
    This handler is called every time the IOCCF2 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF2_SetInterruptHandler(IOCCF2_DefaultInterruptHandler);

*/
void IOCCF2_DefaultInterruptHandler(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/