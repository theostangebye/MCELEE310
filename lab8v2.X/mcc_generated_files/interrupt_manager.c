/**
  Generated Interrupt Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    interrupt_manager.h

  @Summary:
    This is the Interrupt Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description:
    This header file provides implementations for global interrupt handling.
    For individual peripheral handlers please see the peripheral driver for
    all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC18F25Q10
        Driver Version    :  2.12
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.00 or later
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

#include "interrupt_manager.h"
#include "mcc.h"

void  INTERRUPT_Initialize (void)
{
    // Enable Interrupt Priority Vectors
    INTCONbits.IPEN = 1;

    // Assign peripheral interrupt priority vectors

    // TMRI - high priority
    IPR4bits.TMR2IP = 1;


    // TMRI - low priority
    IPR4bits.TMR1IP = 0;    

    // TMRI - low priority
    IPR4bits.TMR3IP = 0;    

    // ADI - low priority
    IPR1bits.ADIP = 0;    

    // CCPI - low priority
    IPR6bits.CCP1IP = 0;    

    // IOCI - low priority
    IPR0bits.IOCIP = 0;    

}

void __interrupt() INTERRUPT_InterruptManagerHigh (void)
{
   // interrupt handler
    if(PIE4bits.TMR2IE == 1 && PIR4bits.TMR2IF == 1)
    {
        TMR2_ISR();
    }
}

void __interrupt(low_priority) INTERRUPT_InterruptManagerLow (void)
{
    // interrupt handler
    if(PIE4bits.TMR1IE == 1 && PIR4bits.TMR1IF == 1)
    {
        TMR1_ISR();
    }
    else if(PIE4bits.TMR3IE == 1 && PIR4bits.TMR3IF == 1)
    {
        TMR3_ISR();
    }
    else if(PIE1bits.ADIE == 1 && PIR1bits.ADIF == 1)
    {
        ADCC_ISR();
    }
    else if(PIE6bits.CCP1IE == 1 && PIR6bits.CCP1IF == 1)
    {
        CCP1_CaptureISR();
    }
    else if(PIE0bits.IOCIE == 1 && PIR0bits.IOCIF == 1)
    {
        PIN_MANAGER_IOC();
    }
    else
    {
        //Unhandled Interrupt
    }
}
/**
 End of File
*/
