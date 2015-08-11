/**
  EXT_INT Generated Driver API Header File 

  @Company:
    Microchip Technology Inc.

  @File Name:
    ext_int.h

  @Summary:
    This is the generated header file for the EXT_INT driver using MPLAB® Code Configurator

  @Description:
    This header file provides APIs for driver for EXT_INT. 
    Generation Information : 
        Product Revision  :  MPLAB® Code Configurator - v2.10
        Device            :  PIC24FJ128GC006
        Driver Version    :  1.0.0
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.23
        MPLAB             :  MPLAB X 2.26
*/

/*
Copyright (c) 2013 - 2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*/

#ifndef _EXT_INT_H
#define _EXT_INT_H

/**
    Section: Includes
*/
#include <xc.h>

// Provide C++ Compatibility
#ifdef __cplusplus  

extern "C" {

#endif

/**
    Section: Macros
*/
/**
  @Summary
    Clears the interrupt flag for INT1

  @Description
    This routine clears the interrupt flag for the external interrupt, INT1.
 
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    void __attribute__ ( ( interrupt, no_auto_psv ) ) _INT1Interrupt(void)
    {
        // User Area Begin->code: INT1 - External Interrupt 1

        // User Area End->code: INT1 - External Interrupt 1
        USB_Charger_Fault_Interupt_InterruptFlagClear();
    }
    </code>

*/
#define USB_Charger_Fault_Interupt_InterruptFlagClear()       (IFS1bits.INT1IF = 0)
#define DRV_USB_Charger_Fault_Interupt_InterruptFlagClear()       (IFS1bits.INT1IF = 0)
/**
  @Summary
    Clears the interrupt enable for INT1

  @Description
    This routine clears the interrupt enable for the external interrupt, INT1.
    After calling this routine, external interrupts on this pin will not be serviced by the 
    interrupt handler, _INT1Interrupt.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    Changing the external interrupt edge detect from negative to positive
    <code>
    // clear the interrupt enable
    USB_Charger_Fault_Interupt_InterruptDisable();
    // change the edge
    USB_Charger_Fault_Interupt_PositiveEdgeSet();
    // clear the interrupt flag and re-enable the interrupt
    USB_Charger_Fault_Interupt_InterruptFlagClear();
    USB_Charger_Fault_Interupt_InterruptEnable();
    </code>

*/
#define USB_Charger_Fault_Interupt_InterruptDisable()     (IEC1bits.INT1IE = 0)
#define DRV_USB_Charger_Fault_Interupt_InterruptDisable()     (IEC1bits.INT1IE = 0)
/**
  @Summary
    Clears the interrupt enable for INT1

  @Description
    This routine clears the interrupt enable for the external interrupt, INT1.
    After calling this routine, external interrupts on this pin will be serviced by the 
    interrupt handler, _INT1Interrupt.
 
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    Setting the external interrupt to handle positive edge interrupts
    <code>
    // set the edge
    USB_Charger_Fault_Interupt_PositiveEdgeSet();
    // clear the interrupt flag and enable the interrupt
    USB_Charger_Fault_Interupt_InterruptFlagClear();
    USB_Charger_Fault_Interupt_InterruptEnable();
    </code>

*/
#define USB_Charger_Fault_Interupt_InterruptEnable()       (IEC1bits.INT1IE = 1)
#define DRV_USB_Charger_Fault_Interupt_InterruptEnable()       (IEC1bits.INT1IE = 1)
/**
  @Summary
    Sets the edge detect of the external interrupt to negative edge.

  @Description
    This routine set the edge detect of the extern interrupt to negative edge.  
    After this routine is called the interrupt flag will be set when the external 
    interrupt pins level transitions from a high to low level.
 
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    Setting the external interrupt to handle negative edge interrupts
    <code>
    // set the edge
    USB_Charger_Fault_Interupt_NegativeEdgeSet();
    // clear the interrupt flag and enable the interrupt
    USB_Charger_Fault_Interupt_InterruptFlagClear();
    USB_Charger_Fault_Interupt_InterruptEnable();
    </code>

*/
#define USB_Charger_Fault_Interupt_NegativeEdgeSet()          (INTCON2bits.INT1EP = 1)
#define DRV_USB_Charger_Fault_Interupt_NegativeEdgeSet()          (INTCON2bits.INT1EP = 1)
/**
  @Summary
    Sets the edge detect of the external interrupt to positive edge.

  @Description
    This routine set the edge detect of the extern interrupt to positive edge.  
    After this routine is called the interrupt flag will be set when the external 
    interrupt pins level transitions from a low to high level.
 
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    Setting the external interrupt to handle positive edge interrupts
    <code>
    // set the edge
    USB_Charger_Fault_Interupt_PositiveEdgeSet();
    // clear the interrupt flag and enable the interrupt
    USB_Charger_Fault_Interupt_InterruptFlagClear();
    USB_Charger_Fault_Interupt_InterruptEnable();
    </code>

*/
#define USB_Charger_Fault_Interupt_PositiveEdgeSet()          (INTCON2bits.INT1EP = 0)
#define DRV_USB_Charger_Fault_Interupt_PositiveEdgeSet()          (INTCON2bits.INT1EP = 0)

/**
    Section: External Interrupt Initializers
 */
/**
  @Summary
    Initializes the external interrupt pins

  @Description
    This routine initializes the EXT_INT driver to detect the configured edge, clear
    the interrupt flag and enable the interrupt.

    The following external interrupts will be initialized:
    INT1 - USB_Charger_Fault_Interupt
 
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    Initialize the external interrupt pins
    <code>
    // 
    EXT_INT_Initialize();
    </code>

*/
void EXT_INT_Initialize(void);
/**
    void DRV_EXT_INT_Initialize(void)
*/
void DRV_EXT_INT_Initialize(void) __attribute__((deprecated ("\nThis will be removed in future MCC releases.\nUse EXT_INT_Initialize instead."))); 

// Provide C++ Compatibility
#ifdef __cplusplus  

}

#endif
#endif
