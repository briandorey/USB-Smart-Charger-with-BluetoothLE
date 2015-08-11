
/******************************************************************************

    Hardware Profile Configuration File
    
This file contains definitions of hardware-specific options.


Software License Agreement

The software supplied herewith by Microchip Technology Incorporated
(the �Company�) for its PICmicro� Microcontroller is intended and
supplied to you, the Company�s customer, for use solely and
exclusively on Microchip PICmicro Microcontroller products. The
software is owned by the Company and/or its supplier, and is
protected under applicable copyright laws. All rights are reserved.
Any use in violation of the foregoing restrictions may subject the
user to criminal sanctions under applicable laws, as well as to
civil liability for the breach of the terms and conditions of this
license.

THIS SOFTWARE IS PROVIDED IN AN �AS IS� CONDITION. NO WARRANTIES,
WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

Author          Date    Comments
--------------------------------------------------------------------------------

 *******************************************************************************/

#ifndef _HARDWARE_PROFILE_H_
#define _HARDWARE_PROFILE_H_

#include <p24Fxxxx.h>



// Various clock values
#define GetSystemClock()            32000000UL
#define GetPeripheralClock()        (GetSystemClock())
#define GetInstructionClock()       (GetSystemClock() / 2)

// Clock values
#define MILLISECONDS_PER_TICK       10
#define TIMER_PRESCALER             TIMER_PRESCALER_8   // 8MHz: TIMER_PRESCALER_1
#define TIMER_PERIOD                20000                // 10ms=20000, 1ms=2000

#define FOSC    (32000000UL)
#define FCY     (FOSC/2)


// Bluetooth defines



//#define USE_USB_PLL


// Define the baud rate constants

#define BAUDRATE2       57600UL
#define BRG_DIV2        4
#define BRGH2           1


/** TRIS ***********************************************************/
#define INPUT_PIN           1
#define OUTPUT_PIN          0

// EEPROM address map

#define EEPROM_VERSION      0x0000
#define EEPROM_XMAX         0x0002
#define EEPROM_XMIN         0x0004
#define EEPROM_YMAX         0x0006
#define EEPROM_YMIN         0x0008

#endif  


