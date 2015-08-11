/**
  EXT_INT Generated Driver File 

  @Company:
    Microchip Technology Inc.

  @File Name:
    ext_int.c

  @Summary
    This is the generated driver implementation file for the EXT_INT 
    driver using MPLAB® Code Configurator

  @Description:
    This source file provides implementations for driver APIs for EXT_INT. 
    Generation Information : 
        Product Revision  :  MPLAB® Code Configurator - v2.10
        Device            :  PIC24FJ128GC006
        Driver Version    :  1.0.0
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.23
        MPLAB             :  MPLAB X 2.26
*/

/**
   Section: Includes
 */
#include <xc.h>
#include "ext_int.h"
//***User Area Begin->code: Add External Interrupt handler specific headers 

//***User Area End->code: Add External Interrupt handler specific headers

/**
   Section: External Interrupt Handlers
 */
/**
  Interrupt Handler for USB_Charger_Fault_Interupt - INT1
*/
void __attribute__ ( ( interrupt, no_auto_psv ) ) _INT1Interrupt(void)
{
    //***User Area Begin->code: INT1 - External Interrupt 1***

    //***User Area End->code: INT1 - External Interrupt 1***
    USB_Charger_Fault_Interupt_InterruptFlagClear();
}
/**
    Section: External Interrupt Initializers
 */
/**
    void EXT_INT_Initialize(void)

    Initializer for the following external interrupts
    INT1
*/
void EXT_INT_Initialize(void)
{
    /*******
     * INT1
     * Clear the interrupt flag
     * Set the external interrupt edge detect
     * Enable the interrupt
     ********/
    USB_Charger_Fault_Interupt_InterruptFlagClear();
    USB_Charger_Fault_Interupt_NegativeEdgeSet();
    USB_Charger_Fault_Interupt_InterruptEnable();
}
/**
    void DRV_EXT_INT_Initialize(void)
*/
void DRV_EXT_INT_Initialize(void)
{
    EXT_INT_Initialize();
}
