
/**
  RTCC Generated Driver API Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    rtcc.c

  @Summary:
    This is the generated header file for the RTCC driver using MPLAB® Code Configurator

  @Description:
    This header file provides APIs for driver for RTCC.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.10
        Device            :  PIC24FJ128GC006
        Driver Version    :  0.5
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.23
        MPLAB 	          :  MPLAB X 2.26
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


/**
 Section: Included Files
*/

#include <xc.h>
#include "rtcc.h"
#include "pin_manager.h"
#include "sdadc1.h"
#include "uart1.h"
#include "../bluetooth.h"
#include "../functions.h"
#include "../main.h"

/**
// Section: Driver Interface Function Definitions
*/


void RTCC_Initialize(void)
{
   // Turn on the secondary oscillator
   __builtin_write_OSCCONL(0x02);

   // Set the RTCWREN bit
   __builtin_write_RTCWEN();

   RCFGCALbits.RTCEN = 0;

   // set Sun Dec 28 10:37:06 GMT 2014
   RCFGCALbits.RTCPTR = 3;        // start the sequence
   RTCVAL = 0x14;    // YEAR
   RTCVAL = 0x1228;    // MONTH-1/DAY-1
   RTCVAL = 0x10;    // WEEKDAY/HOURS
   RTCVAL = 0x3706;    // MINUTES/SECONDS

   // set Sun Dec 28 10:37:06 GMT 2014
   ALCFGRPTbits.ALRMEN = 0;
   ALCFGRPTbits.ALRMPTR = 2;
   ALRMVAL = 0x1228;
   ALRMVAL = 0x10;
   ALRMVAL = 0x3706;

   // ALRMEN enabled; ARPT 0x0000; AMASK Every Second; CHIME enabled; ALRMPTR MIN_SEC; 
   ALCFGRPT = 0xC400;
   // PWCPOL disabled; PWCEN disabled; RTCLK SOSC; PWCPRE disabled; RTCOUT Alarm Pulse; PWSPRE disabled; 
   RTCPWC = 0x0000;
           
   // Enable RTCC, clear RTCWREN
   RCFGCALbits.RTCEN = 1;
   RCFGCALbits.RTCWREN = 0;

   IEC3bits.RTCIE = 1;
}
/**
    void DRV_RTCC_Initialize (void)
*/
void DRV_RTCC_Initialize (void)
{
    RTCC_Initialize();
}


/**
 This function implements RTCC_TimeGet. It access the 
 registers of  RTCC and writes to them the values provided 
 in the function argument currentTime
*/

bool RTCC_TimeGet(struct tm *currentTime)
{
    uint16_t register_value;
    if(RCFGCALbits.RTCSYNC){
        return false;
    }

   // Set the RTCWREN bit
   __builtin_write_RTCWEN();

    RCFGCALbits.RTCPTR = 3;
    register_value = RTCVAL;
    currentTime->tm_year = ((((register_value & 0x00FF) & 0xF0) >> 4)* 10 + ((register_value & 0x00FF) & 0x0F));
    RCFGCALbits.RTCPTR = 2;
    register_value = RTCVAL;
    currentTime->tm_mon = (((((register_value & 0xFF00) >> 8) & 0xF0) >> 4)* 10 +  (((register_value & 0xFF00) >> 8) & 0x0F));
    currentTime->tm_mday = ((((register_value & 0x00FF) & 0xF0) >> 4)* 10 + ((register_value & 0x00FF) & 0x0F));
    RCFGCALbits.RTCPTR = 1;
    register_value = RTCVAL;
    currentTime->tm_wday = (((((register_value & 0xFF00) >> 8) & 0xF0) >> 4)* 10 +  (((register_value & 0xFF00) >> 8) & 0x0F));
    currentTime->tm_hour = ((((register_value & 0x00FF) & 0xF0) >> 4)* 10 + ((register_value & 0x00FF) & 0x0F));
    RCFGCALbits.RTCPTR = 0;
    register_value = RTCVAL;
    currentTime->tm_min = (((((register_value & 0xFF00) >> 8) & 0xF0) >> 4)* 10 +  (((register_value & 0xFF00) >> 8) & 0x0F));
    currentTime->tm_sec = ((((register_value & 0x00FF) & 0xF0) >> 4)* 10 + ((register_value & 0x00FF) & 0x0F));
    RCFGCALbits.RTCWREN = 0;

    return true;
}
/**
    bool DRV_RTCC_TimeGet(struct tm *currentTime)
*/
bool DRV_RTCC_TimeGet(struct tm *currentTime)
{
    return(RTCC_TimeGet(currentTime));
}

/**
 This function sets the RTCC value
*/
void RTCC_TimeSet(struct tm * initialTime)
{
   // Set the RTCWREN bit
   __builtin_write_RTCWEN();

   RCFGCALbits.RTCEN = 0;
   
   IFS3bits.RTCIF = false;
   IEC3bits.RTCIE = 0;

   // set RTCC initial time
   RCFGCALbits.RTCPTR = 3;                               // start the sequence
   RTCVAL = initialTime->tm_year;                        // YEAR
   RTCVAL = (initialTime->tm_mon << 8) | initialTime->tm_mday;  // MONTH-1/DAY-1
   RTCVAL = (initialTime->tm_wday << 8) | initialTime->tm_hour; // WEEKDAY/HOURS
   RTCVAL = (initialTime->tm_min << 8) | initialTime->tm_sec;   // MINUTES/SECONDS   
           
   // Enable RTCC, clear RTCWREN         
   RCFGCALbits.RTCEN = 1;  
   RCFGCALbits.RTCWREN = 0;

   IEC3bits.RTCIE = 1;

}

/* Function:
    void __attribute__ ( ( interrupt, no_auto_psv ) ) _ISR _RTCCInterrupt( void )

  Summary:
    Interrupt Service Routine for the RTCC Peripheral

  Description:
    This is the interrupt service routine for the RTCC peripheral. Add in code if 
    required in the ISR. 
*/

double fResult = 0; // tempory value used in the ADC conversion

double input_voltage = 0;



void __attribute__ ( ( interrupt, no_auto_psv ) ) _ISR _RTCCInterrupt( void )
{
    /* TODO : Add interrupt handling code */

    // get the adc value for the 5v usb current shunt

    bool bConversionComplete = false;

    // check if a usb device is connected, if so get the power usage from the ADC
    //if (DeviceStatus){
        SDADC1_InitializeADC0();
        while (1)
        {
            bConversionComplete = SDADC1_IsConversionComplete();
            if(true == bConversionComplete)
            {
                fResult = SDADC1_ConversionResultGet();
                break;
            }
        }

        calculateUSBPower(fResult);
        

        if (CurrentPowerUsage > 0.1){
            if (DeviceStatus == false){
                 // reset the total charge value to 0
                TotalCharge = 0;

                // set the start time from the RTC
                while(!RTCC_TimeGet(&startTime)){};
                endTime = startTime;
                // set the end time to be the same as the start time
                DeviceStatus = true;
                LED_GREEN_SetHigh();
            }
            
        }
        else{
            if (DeviceStatus == true){
                DeviceStatus = false;
                LED_GREEN_SetLow();
                while(!RTCC_TimeGet(&endTime)){};
            }
        }

   
    // get adc value for the input voltage


    SDADC1_InitializeADC1();
    while (1)
    {
	bConversionComplete = SDADC1_IsConversionComplete();
        if(true == bConversionComplete)
        {
            fResult = SDADC1_ConversionResultGet();
            break;
        }
    }
   
     input_voltage = calculateInputVoltage(fResult); // calculate the power supply voltage based on the adc input

 
    if (input_voltage < PowerDownVoltage){
        // turn off the 5V psu

        if (IsSleeping == 0){
            blinkRed();
            blinkRed();
            Power_Enable_SetLow();
            USB_Charger_Enable_SetLow();
        }

        IsSleeping = 1;

        Sleep();

    }

    else if ((input_voltage > PowerUpVoltage)){
        if (IsSleeping == 1){
            // device was in sleep mode so reinitialise the bluetooth device and power on the 5V regulator
            
            Power_Enable_SetHigh();
            USB_Charger_Enable_SetHigh();
            IsSleeping = 0;
            //initBluetooth();
            blinkGreen();
            blinkGreen();
        }



    }

    DoUpdate = true;

    IFS3bits.RTCIF = false;
}


/**
 End of File
*/
