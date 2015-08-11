/**
  System Interrupts Generated Driver File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the generated manager file for the MPLAB® Code Configurator device.  This manager
    configures the pins direction, initial state, analog setting.
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Description:
    This source file provides implementations for MPLAB® Code Configurator interrupts.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.10
        Device            :  PIC24FJ128GC006
        Version           :  1.02
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

#ifndef _PIN_MANAGER_H
#define _PIN_MANAGER_H
/**
    Section: Includes
*/
#include <xc.h>
/**
    Section: Device Pin Macros
*/
/**
  @Summary
    Sets the GPIO pin, RB4, high using LATB4.

  @Description
    Sets the GPIO pin, RB4, high using LATB4.

  @Preconditions
    The RB4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB4 high (1)
    Power_Enable_SetHigh();
    </code>

*/
#define Power_Enable_SetHigh()          _LATB4 = 1
/**
  @Summary
    Sets the GPIO pin, RB4, low using LATB4.

  @Description
    Sets the GPIO pin, RB4, low using LATB4.

  @Preconditions
    The RB4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB4 low (0)
    Power_Enable_SetLow();
    </code>

*/
#define Power_Enable_SetLow()           _LATB4 = 0
/**
  @Summary
    Toggles the GPIO pin, RB4, using LATB4.

  @Description
    Toggles the GPIO pin, RB4, using LATB4.

  @Preconditions
    The RB4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB4
    Power_Enable_SetToggle();
    </code>

*/
#define Power_Enable_Toggle()           _LATB4 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RB4.

  @Description
    Reads the value of the GPIO pin, RB4.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB4
    postValue = Power_Enable_GetValue();
    </code>

*/
#define Power_Enable_GetValue()         _RB4
/**
  @Summary
    Configures the GPIO pin, RB4, as an input.

  @Description
    Configures the GPIO pin, RB4, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB4 as an input
    Power_Enable_SetDigitalInput();
    </code>

*/
#define Power_Enable_SetDigitalInput()  _TRISB4 = 1
/**
  @Summary
    Configures the GPIO pin, RB4, as an output.

  @Description
    Configures the GPIO pin, RB4, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB4 as an output
    Power_Enable_SetDigitalOutput();
    </code>

*/
#define Power_Enable_SetDigitalOutput() _TRISB4 = 0
/**
  @Summary
    Sets the GPIO pin, RB12, high using LATB12.

  @Description
    Sets the GPIO pin, RB12, high using LATB12.

  @Preconditions
    The RB12 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB12 high (1)
    LED_GREEN_SetHigh();
    </code>

*/
#define LED_GREEN_SetHigh()          _LATB12 = 1
/**
  @Summary
    Sets the GPIO pin, RB12, low using LATB12.

  @Description
    Sets the GPIO pin, RB12, low using LATB12.

  @Preconditions
    The RB12 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB12 low (0)
    LED_GREEN_SetLow();
    </code>

*/
#define LED_GREEN_SetLow()           _LATB12 = 0
/**
  @Summary
    Toggles the GPIO pin, RB12, using LATB12.

  @Description
    Toggles the GPIO pin, RB12, using LATB12.

  @Preconditions
    The RB12 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB12
    LED_GREEN_SetToggle();
    </code>

*/
#define LED_GREEN_Toggle()           _LATB12 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RB12.

  @Description
    Reads the value of the GPIO pin, RB12.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB12
    postValue = LED_GREEN_GetValue();
    </code>

*/
#define LED_GREEN_GetValue()         _RB12
/**
  @Summary
    Configures the GPIO pin, RB12, as an input.

  @Description
    Configures the GPIO pin, RB12, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB12 as an input
    LED_GREEN_SetDigitalInput();
    </code>

*/
#define LED_GREEN_SetDigitalInput()  _TRISB12 = 1
/**
  @Summary
    Configures the GPIO pin, RB12, as an output.

  @Description
    Configures the GPIO pin, RB12, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB12 as an output
    LED_GREEN_SetDigitalOutput();
    </code>

*/
#define LED_GREEN_SetDigitalOutput() _TRISB12 = 0
/**
  @Summary
    Sets the GPIO pin, RB13, high using LATB13.

  @Description
    Sets the GPIO pin, RB13, high using LATB13.

  @Preconditions
    The RB13 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB13 high (1)
    LED_RED_SetHigh();
    </code>

*/
#define LED_RED_SetHigh()          _LATB13 = 1
/**
  @Summary
    Sets the GPIO pin, RB13, low using LATB13.

  @Description
    Sets the GPIO pin, RB13, low using LATB13.

  @Preconditions
    The RB13 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB13 low (0)
    LED_RED_SetLow();
    </code>

*/
#define LED_RED_SetLow()           _LATB13 = 0
/**
  @Summary
    Toggles the GPIO pin, RB13, using LATB13.

  @Description
    Toggles the GPIO pin, RB13, using LATB13.

  @Preconditions
    The RB13 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB13
    LED_RED_SetToggle();
    </code>

*/
#define LED_RED_Toggle()           _LATB13 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RB13.

  @Description
    Reads the value of the GPIO pin, RB13.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB13
    postValue = LED_RED_GetValue();
    </code>

*/
#define LED_RED_GetValue()         _RB13
/**
  @Summary
    Configures the GPIO pin, RB13, as an input.

  @Description
    Configures the GPIO pin, RB13, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB13 as an input
    LED_RED_SetDigitalInput();
    </code>

*/
#define LED_RED_SetDigitalInput()  _TRISB13 = 1
/**
  @Summary
    Configures the GPIO pin, RB13, as an output.

  @Description
    Configures the GPIO pin, RB13, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB13 as an output
    LED_RED_SetDigitalOutput();
    </code>

*/
#define LED_RED_SetDigitalOutput() _TRISB13 = 0
/**
  @Summary
    Sets the GPIO pin, RB14, high using LATB14.

  @Description
    Sets the GPIO pin, RB14, high using LATB14.

  @Preconditions
    The RB14 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB14 high (1)
    USB_Charger_Fault_Interupt_SetHigh();
    </code>

*/
#define USB_Charger_Fault_Interupt_SetHigh()          _LATB14 = 1
/**
  @Summary
    Sets the GPIO pin, RB14, low using LATB14.

  @Description
    Sets the GPIO pin, RB14, low using LATB14.

  @Preconditions
    The RB14 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB14 low (0)
    USB_Charger_Fault_Interupt_SetLow();
    </code>

*/
#define USB_Charger_Fault_Interupt_SetLow()           _LATB14 = 0
/**
  @Summary
    Toggles the GPIO pin, RB14, using LATB14.

  @Description
    Toggles the GPIO pin, RB14, using LATB14.

  @Preconditions
    The RB14 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB14
    USB_Charger_Fault_Interupt_SetToggle();
    </code>

*/
#define USB_Charger_Fault_Interupt_Toggle()           _LATB14 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RB14.

  @Description
    Reads the value of the GPIO pin, RB14.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB14
    postValue = USB_Charger_Fault_Interupt_GetValue();
    </code>

*/
#define USB_Charger_Fault_Interupt_GetValue()         _RB14
/**
  @Summary
    Configures the GPIO pin, RB14, as an input.

  @Description
    Configures the GPIO pin, RB14, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB14 as an input
    USB_Charger_Fault_Interupt_SetDigitalInput();
    </code>

*/
#define USB_Charger_Fault_Interupt_SetDigitalInput()  _TRISB14 = 1
/**
  @Summary
    Configures the GPIO pin, RB14, as an output.

  @Description
    Configures the GPIO pin, RB14, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB14 as an output
    USB_Charger_Fault_Interupt_SetDigitalOutput();
    </code>

*/
#define USB_Charger_Fault_Interupt_SetDigitalOutput() _TRISB14 = 0
/**
  @Summary
    Sets the GPIO pin, RB15, high using LATB15.

  @Description
    Sets the GPIO pin, RB15, high using LATB15.

  @Preconditions
    The RB15 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB15 high (1)
    USB_Charger_Enable_SetHigh();
    </code>

*/
#define USB_Charger_Enable_SetHigh()          _LATB15 = 1
/**
  @Summary
    Sets the GPIO pin, RB15, low using LATB15.

  @Description
    Sets the GPIO pin, RB15, low using LATB15.

  @Preconditions
    The RB15 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB15 low (0)
    USB_Charger_Enable_SetLow();
    </code>

*/
#define USB_Charger_Enable_SetLow()           _LATB15 = 0
/**
  @Summary
    Toggles the GPIO pin, RB15, using LATB15.

  @Description
    Toggles the GPIO pin, RB15, using LATB15.

  @Preconditions
    The RB15 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB15
    USB_Charger_Enable_SetToggle();
    </code>

*/
#define USB_Charger_Enable_Toggle()           _LATB15 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RB15.

  @Description
    Reads the value of the GPIO pin, RB15.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB15
    postValue = USB_Charger_Enable_GetValue();
    </code>

*/
#define USB_Charger_Enable_GetValue()         _RB15
/**
  @Summary
    Configures the GPIO pin, RB15, as an input.

  @Description
    Configures the GPIO pin, RB15, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB15 as an input
    USB_Charger_Enable_SetDigitalInput();
    </code>

*/
#define USB_Charger_Enable_SetDigitalInput()  _TRISB15 = 1
/**
  @Summary
    Configures the GPIO pin, RB15, as an output.

  @Description
    Configures the GPIO pin, RB15, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB15 as an output
    USB_Charger_Enable_SetDigitalOutput();
    </code>

*/
#define USB_Charger_Enable_SetDigitalOutput() _TRISB15 = 0
/**
  @Summary
    Sets the GPIO pin, RD0, high using LATD0.

  @Description
    Sets the GPIO pin, RD0, high using LATD0.

  @Preconditions
    The RD0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD0 high (1)
    BT_CMD_SetHigh();
    </code>

*/
#define BT_CMD_SetHigh()          _LATD0 = 1
/**
  @Summary
    Sets the GPIO pin, RD0, low using LATD0.

  @Description
    Sets the GPIO pin, RD0, low using LATD0.

  @Preconditions
    The RD0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD0 low (0)
    BT_CMD_SetLow();
    </code>

*/
#define BT_CMD_SetLow()           _LATD0 = 0
/**
  @Summary
    Toggles the GPIO pin, RD0, using LATD0.

  @Description
    Toggles the GPIO pin, RD0, using LATD0.

  @Preconditions
    The RD0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RD0
    BT_CMD_SetToggle();
    </code>

*/
#define BT_CMD_Toggle()           _LATD0 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RD0.

  @Description
    Reads the value of the GPIO pin, RD0.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RD0
    postValue = BT_CMD_GetValue();
    </code>

*/
#define BT_CMD_GetValue()         _RD0
/**
  @Summary
    Configures the GPIO pin, RD0, as an input.

  @Description
    Configures the GPIO pin, RD0, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD0 as an input
    BT_CMD_SetDigitalInput();
    </code>

*/
#define BT_CMD_SetDigitalInput()  _TRISD0 = 1
/**
  @Summary
    Configures the GPIO pin, RD0, as an output.

  @Description
    Configures the GPIO pin, RD0, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD0 as an output
    BT_CMD_SetDigitalOutput();
    </code>

*/
#define BT_CMD_SetDigitalOutput() _TRISD0 = 0
/**
  @Summary
    Sets the GPIO pin, RD1, high using LATD1.

  @Description
    Sets the GPIO pin, RD1, high using LATD1.

  @Preconditions
    The RD1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD1 high (1)
    U1RTS_SetHigh();
    </code>

*/
#define U1RTS_SetHigh()          _LATD1 = 1
/**
  @Summary
    Sets the GPIO pin, RD1, low using LATD1.

  @Description
    Sets the GPIO pin, RD1, low using LATD1.

  @Preconditions
    The RD1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD1 low (0)
    U1RTS_SetLow();
    </code>

*/
#define U1RTS_SetLow()           _LATD1 = 0
/**
  @Summary
    Toggles the GPIO pin, RD1, using LATD1.

  @Description
    Toggles the GPIO pin, RD1, using LATD1.

  @Preconditions
    The RD1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RD1
    U1RTS_SetToggle();
    </code>

*/
#define U1RTS_Toggle()           _LATD1 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RD1.

  @Description
    Reads the value of the GPIO pin, RD1.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RD1
    postValue = U1RTS_GetValue();
    </code>

*/
#define U1RTS_GetValue()         _RD1
/**
  @Summary
    Configures the GPIO pin, RD1, as an input.

  @Description
    Configures the GPIO pin, RD1, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD1 as an input
    U1RTS_SetDigitalInput();
    </code>

*/
#define U1RTS_SetDigitalInput()  _TRISD1 = 1
/**
  @Summary
    Configures the GPIO pin, RD1, as an output.

  @Description
    Configures the GPIO pin, RD1, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD1 as an output
    U1RTS_SetDigitalOutput();
    </code>

*/
#define U1RTS_SetDigitalOutput() _TRISD1 = 0
/**
  @Summary
    Sets the GPIO pin, RD2, high using LATD2.

  @Description
    Sets the GPIO pin, RD2, high using LATD2.

  @Preconditions
    The RD2 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD2 high (1)
    BT_WAKE_HW_SetHigh();
    </code>

*/
#define BT_WAKE_HW_SetHigh()          _LATD2 = 1
/**
  @Summary
    Sets the GPIO pin, RD2, low using LATD2.

  @Description
    Sets the GPIO pin, RD2, low using LATD2.

  @Preconditions
    The RD2 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD2 low (0)
    BT_WAKE_HW_SetLow();
    </code>

*/
#define BT_WAKE_HW_SetLow()           _LATD2 = 0
/**
  @Summary
    Toggles the GPIO pin, RD2, using LATD2.

  @Description
    Toggles the GPIO pin, RD2, using LATD2.

  @Preconditions
    The RD2 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RD2
    BT_WAKE_HW_SetToggle();
    </code>

*/
#define BT_WAKE_HW_Toggle()           _LATD2 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RD2.

  @Description
    Reads the value of the GPIO pin, RD2.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RD2
    postValue = BT_WAKE_HW_GetValue();
    </code>

*/
#define BT_WAKE_HW_GetValue()         _RD2
/**
  @Summary
    Configures the GPIO pin, RD2, as an input.

  @Description
    Configures the GPIO pin, RD2, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD2 as an input
    BT_WAKE_HW_SetDigitalInput();
    </code>

*/
#define BT_WAKE_HW_SetDigitalInput()  _TRISD2 = 1
/**
  @Summary
    Configures the GPIO pin, RD2, as an output.

  @Description
    Configures the GPIO pin, RD2, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD2 as an output
    BT_WAKE_HW_SetDigitalOutput();
    </code>

*/
#define BT_WAKE_HW_SetDigitalOutput() _TRISD2 = 0
/**
  @Summary
    Sets the GPIO pin, RD3, high using LATD3.

  @Description
    Sets the GPIO pin, RD3, high using LATD3.

  @Preconditions
    The RD3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD3 high (1)
    U1CTS_SetHigh();
    </code>

*/
#define U1CTS_SetHigh()          _LATD3 = 1
/**
  @Summary
    Sets the GPIO pin, RD3, low using LATD3.

  @Description
    Sets the GPIO pin, RD3, low using LATD3.

  @Preconditions
    The RD3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD3 low (0)
    U1CTS_SetLow();
    </code>

*/
#define U1CTS_SetLow()           _LATD3 = 0
/**
  @Summary
    Toggles the GPIO pin, RD3, using LATD3.

  @Description
    Toggles the GPIO pin, RD3, using LATD3.

  @Preconditions
    The RD3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RD3
    U1CTS_SetToggle();
    </code>

*/
#define U1CTS_Toggle()           _LATD3 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RD3.

  @Description
    Reads the value of the GPIO pin, RD3.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RD3
    postValue = U1CTS_GetValue();
    </code>

*/
#define U1CTS_GetValue()         _RD3
/**
  @Summary
    Configures the GPIO pin, RD3, as an input.

  @Description
    Configures the GPIO pin, RD3, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD3 as an input
    U1CTS_SetDigitalInput();
    </code>

*/
#define U1CTS_SetDigitalInput()  _TRISD3 = 1
/**
  @Summary
    Configures the GPIO pin, RD3, as an output.

  @Description
    Configures the GPIO pin, RD3, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD3 as an output
    U1CTS_SetDigitalOutput();
    </code>

*/
#define U1CTS_SetDigitalOutput() _TRISD3 = 0
/**
  @Summary
    Sets the GPIO pin, RD8, high using LATD8.

  @Description
    Sets the GPIO pin, RD8, high using LATD8.

  @Preconditions
    The RD8 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD8 high (1)
    U1RX_SetHigh();
    </code>

*/
#define U1RX_SetHigh()          _LATD8 = 1
/**
  @Summary
    Sets the GPIO pin, RD8, low using LATD8.

  @Description
    Sets the GPIO pin, RD8, low using LATD8.

  @Preconditions
    The RD8 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD8 low (0)
    U1RX_SetLow();
    </code>

*/
#define U1RX_SetLow()           _LATD8 = 0
/**
  @Summary
    Toggles the GPIO pin, RD8, using LATD8.

  @Description
    Toggles the GPIO pin, RD8, using LATD8.

  @Preconditions
    The RD8 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RD8
    U1RX_SetToggle();
    </code>

*/
#define U1RX_Toggle()           _LATD8 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RD8.

  @Description
    Reads the value of the GPIO pin, RD8.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RD8
    postValue = U1RX_GetValue();
    </code>

*/
#define U1RX_GetValue()         _RD8
/**
  @Summary
    Configures the GPIO pin, RD8, as an input.

  @Description
    Configures the GPIO pin, RD8, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD8 as an input
    U1RX_SetDigitalInput();
    </code>

*/
#define U1RX_SetDigitalInput()  _TRISD8 = 1
/**
  @Summary
    Configures the GPIO pin, RD8, as an output.

  @Description
    Configures the GPIO pin, RD8, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD8 as an output
    U1RX_SetDigitalOutput();
    </code>

*/
#define U1RX_SetDigitalOutput() _TRISD8 = 0
/**
  @Summary
    Sets the GPIO pin, RD9, high using LATD9.

  @Description
    Sets the GPIO pin, RD9, high using LATD9.

  @Preconditions
    The RD9 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD9 high (1)
    U1TX_SetHigh();
    </code>

*/
#define U1TX_SetHigh()          _LATD9 = 1
/**
  @Summary
    Sets the GPIO pin, RD9, low using LATD9.

  @Description
    Sets the GPIO pin, RD9, low using LATD9.

  @Preconditions
    The RD9 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD9 low (0)
    U1TX_SetLow();
    </code>

*/
#define U1TX_SetLow()           _LATD9 = 0
/**
  @Summary
    Toggles the GPIO pin, RD9, using LATD9.

  @Description
    Toggles the GPIO pin, RD9, using LATD9.

  @Preconditions
    The RD9 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RD9
    U1TX_SetToggle();
    </code>

*/
#define U1TX_Toggle()           _LATD9 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RD9.

  @Description
    Reads the value of the GPIO pin, RD9.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RD9
    postValue = U1TX_GetValue();
    </code>

*/
#define U1TX_GetValue()         _RD9
/**
  @Summary
    Configures the GPIO pin, RD9, as an input.

  @Description
    Configures the GPIO pin, RD9, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD9 as an input
    U1TX_SetDigitalInput();
    </code>

*/
#define U1TX_SetDigitalInput()  _TRISD9 = 1
/**
  @Summary
    Configures the GPIO pin, RD9, as an output.

  @Description
    Configures the GPIO pin, RD9, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD9 as an output
    U1TX_SetDigitalOutput();
    </code>

*/
#define U1TX_SetDigitalOutput() _TRISD9 = 0
/**
  @Summary
    Sets the GPIO pin, RD11, high using LATD11.

  @Description
    Sets the GPIO pin, RD11, high using LATD11.

  @Preconditions
    The RD11 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD11 high (1)
    BT_Wake_SW_SetHigh();
    </code>

*/
#define BT_Wake_SW_SetHigh()          _LATD11 = 1
/**
  @Summary
    Sets the GPIO pin, RD11, low using LATD11.

  @Description
    Sets the GPIO pin, RD11, low using LATD11.

  @Preconditions
    The RD11 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD11 low (0)
    BT_Wake_SW_SetLow();
    </code>

*/
#define BT_Wake_SW_SetLow()           _LATD11 = 0
/**
  @Summary
    Toggles the GPIO pin, RD11, using LATD11.

  @Description
    Toggles the GPIO pin, RD11, using LATD11.

  @Preconditions
    The RD11 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RD11
    BT_Wake_SW_SetToggle();
    </code>

*/
#define BT_Wake_SW_Toggle()           _LATD11 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RD11.

  @Description
    Reads the value of the GPIO pin, RD11.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RD11
    postValue = BT_Wake_SW_GetValue();
    </code>

*/
#define BT_Wake_SW_GetValue()         _RD11
/**
  @Summary
    Configures the GPIO pin, RD11, as an input.

  @Description
    Configures the GPIO pin, RD11, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD11 as an input
    BT_Wake_SW_SetDigitalInput();
    </code>

*/
#define BT_Wake_SW_SetDigitalInput()  _TRISD11 = 1
/**
  @Summary
    Configures the GPIO pin, RD11, as an output.

  @Description
    Configures the GPIO pin, RD11, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD11 as an output
    BT_Wake_SW_SetDigitalOutput();
    </code>

*/
#define BT_Wake_SW_SetDigitalOutput() _TRISD11 = 0
/**
  @Summary
    Sets the GPIO pin, RF3, high using LATF3.

  @Description
    Sets the GPIO pin, RF3, high using LATF3.

  @Preconditions
    The RF3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RF3 high (1)
    USB_Charger_CTL3_SetHigh();
    </code>

*/
#define USB_Charger_CTL3_SetHigh()          _LATF3 = 1
/**
  @Summary
    Sets the GPIO pin, RF3, low using LATF3.

  @Description
    Sets the GPIO pin, RF3, low using LATF3.

  @Preconditions
    The RF3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RF3 low (0)
    USB_Charger_CTL3_SetLow();
    </code>

*/
#define USB_Charger_CTL3_SetLow()           _LATF3 = 0
/**
  @Summary
    Toggles the GPIO pin, RF3, using LATF3.

  @Description
    Toggles the GPIO pin, RF3, using LATF3.

  @Preconditions
    The RF3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RF3
    USB_Charger_CTL3_SetToggle();
    </code>

*/
#define USB_Charger_CTL3_Toggle()           _LATF3 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RF3.

  @Description
    Reads the value of the GPIO pin, RF3.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RF3
    postValue = USB_Charger_CTL3_GetValue();
    </code>

*/
#define USB_Charger_CTL3_GetValue()         _RF3
/**
  @Summary
    Configures the GPIO pin, RF3, as an input.

  @Description
    Configures the GPIO pin, RF3, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RF3 as an input
    USB_Charger_CTL3_SetDigitalInput();
    </code>

*/
#define USB_Charger_CTL3_SetDigitalInput()  _TRISF3 = 1
/**
  @Summary
    Configures the GPIO pin, RF3, as an output.

  @Description
    Configures the GPIO pin, RF3, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RF3 as an output
    USB_Charger_CTL3_SetDigitalOutput();
    </code>

*/
#define USB_Charger_CTL3_SetDigitalOutput() _TRISF3 = 0
/**
  @Summary
    Sets the GPIO pin, RF4, high using LATF4.

  @Description
    Sets the GPIO pin, RF4, high using LATF4.

  @Preconditions
    The RF4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RF4 high (1)
    USB_Charger_CTL1_SetHigh();
    </code>

*/
#define USB_Charger_CTL1_SetHigh()          _LATF4 = 1
/**
  @Summary
    Sets the GPIO pin, RF4, low using LATF4.

  @Description
    Sets the GPIO pin, RF4, low using LATF4.

  @Preconditions
    The RF4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RF4 low (0)
    USB_Charger_CTL1_SetLow();
    </code>

*/
#define USB_Charger_CTL1_SetLow()           _LATF4 = 0
/**
  @Summary
    Toggles the GPIO pin, RF4, using LATF4.

  @Description
    Toggles the GPIO pin, RF4, using LATF4.

  @Preconditions
    The RF4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RF4
    USB_Charger_CTL1_SetToggle();
    </code>

*/
#define USB_Charger_CTL1_Toggle()           _LATF4 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RF4.

  @Description
    Reads the value of the GPIO pin, RF4.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RF4
    postValue = USB_Charger_CTL1_GetValue();
    </code>

*/
#define USB_Charger_CTL1_GetValue()         _RF4
/**
  @Summary
    Configures the GPIO pin, RF4, as an input.

  @Description
    Configures the GPIO pin, RF4, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RF4 as an input
    USB_Charger_CTL1_SetDigitalInput();
    </code>

*/
#define USB_Charger_CTL1_SetDigitalInput()  _TRISF4 = 1
/**
  @Summary
    Configures the GPIO pin, RF4, as an output.

  @Description
    Configures the GPIO pin, RF4, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RF4 as an output
    USB_Charger_CTL1_SetDigitalOutput();
    </code>

*/
#define USB_Charger_CTL1_SetDigitalOutput() _TRISF4 = 0
/**
  @Summary
    Sets the GPIO pin, RF5, high using LATF5.

  @Description
    Sets the GPIO pin, RF5, high using LATF5.

  @Preconditions
    The RF5 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RF5 high (1)
    USB_Charger_CTL2_SetHigh();
    </code>

*/
#define USB_Charger_CTL2_SetHigh()          _LATF5 = 1
/**
  @Summary
    Sets the GPIO pin, RF5, low using LATF5.

  @Description
    Sets the GPIO pin, RF5, low using LATF5.

  @Preconditions
    The RF5 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RF5 low (0)
    USB_Charger_CTL2_SetLow();
    </code>

*/
#define USB_Charger_CTL2_SetLow()           _LATF5 = 0
/**
  @Summary
    Toggles the GPIO pin, RF5, using LATF5.

  @Description
    Toggles the GPIO pin, RF5, using LATF5.

  @Preconditions
    The RF5 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RF5
    USB_Charger_CTL2_SetToggle();
    </code>

*/
#define USB_Charger_CTL2_Toggle()           _LATF5 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RF5.

  @Description
    Reads the value of the GPIO pin, RF5.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RF5
    postValue = USB_Charger_CTL2_GetValue();
    </code>

*/
#define USB_Charger_CTL2_GetValue()         _RF5
/**
  @Summary
    Configures the GPIO pin, RF5, as an input.

  @Description
    Configures the GPIO pin, RF5, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RF5 as an input
    USB_Charger_CTL2_SetDigitalInput();
    </code>

*/
#define USB_Charger_CTL2_SetDigitalInput()  _TRISF5 = 1
/**
  @Summary
    Configures the GPIO pin, RF5, as an output.

  @Description
    Configures the GPIO pin, RF5, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RF5 as an output
    USB_Charger_CTL2_SetDigitalOutput();
    </code>

*/
#define USB_Charger_CTL2_SetDigitalOutput() _TRISF5 = 0

/**
    Section: Function Prototypes
*/
/**
  @Summary
    Configures the pin settings of the PIC24FJ128GC006
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Description
    This is the generated manager file for the MPLAB® Code Configurator device.  This manager
    configures the pins direction, initial state, analog setting.
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    void SYSTEM_Initialize(void)
    {
        // Other initializers are called from this function
        PIN_MANAGER_Initialize();
    }
    </code>

*/
void PIN_MANAGER_Initialize(void);

#endif
