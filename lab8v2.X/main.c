/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC18F25Q10
        Driver Version    :  2.00
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

#include "mcc_generated_files/mcc.h"
#include "car_ctrl.h"

/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    carcontrol_init();
    __delay_ms(1000);
    
    carcontrol_steering(0);
    
    int i;
    for (i=0; i<80; i++) {
        carcontrol_throttle(i);
        __delay_ms(33);
    }
    for (i=0; i<80; i++) {
        carcontrol_throttle(80-i);
        __delay_ms(33);
    }

//    carcontrol_throttle(22);

    
    for (i=0; i<28; i++) {
        carcontrol_steering(i);
        __delay_ms(25);
    }
    for (i=0; i<28; i++) {
        carcontrol_steering(28-i);
        __delay_ms(30);
    }
    for (i=0; i<30; i++) {
        carcontrol_steering(-i);
        __delay_ms(30);
    }
    for (i=0; i<30; i++) {
        carcontrol_steering(-30+i);
        __delay_ms(30);
    }
        for (i=0; i<28; i++) {
        carcontrol_steering(i);
        __delay_ms(30);
    }
    for (i=0; i<28; i++) {
        carcontrol_steering(28-i);
        __delay_ms(30);
    }
    for (i=0; i<30; i++) {
        carcontrol_steering(-i);
        __delay_ms(30);
    }
    for (i=0; i<30; i++) {
        carcontrol_steering(-30+i);
        __delay_ms(30);
    }
    
    carcontrol_throttle(0);
    
    while (1)
    {   
        carcontrol_steering(0);
    }
}
/**
 End of File
*/