/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB® Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.10
        Device            :  PIC24FJ128GC006
        Driver Version    :  2.00
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




#include "HardwareProfile.h"
#include "functions.h"
#include "usb_config.h"
#include "USB/usb.h"
#include "USB/usb_host_charger.h"
#include "mcc_generated_files/mcc.h"
#include "bluetooth.h"

// *****************************************************************************
// *****************************************************************************
// Constants
// *****************************************************************************
// *****************************************************************************

#define MAX_ALLOWED_CURRENT                 1500

// *****************************************************************************
// *****************************************************************************
// Internal Function Prototypes
// *****************************************************************************
// *****************************************************************************

void    MonitorVBUS( void );


// *****************************************************************************
// *****************************************************************************
// Global Variables
// *****************************************************************************
// *****************************************************************************

BOOL overcurrentStateUSB = false;        // We really only need a bit here.
BOOL DeviceStatus = false;  // show if a device is connected
BOOL IsSleeping = false;

BOOL DoUpdate = false; // used by the RTC alarm interrupt to tell the main loop that a bluetooth variable update is required

double CurrentPowerUsage = 0; // current power usage for the connected device
double PowerDownVoltage = 12.2; // voltage at which the charger will go to sleep
double PowerUpVoltage = 12.8; // voltage at which the charger will wake from sleep
double TotalCharge = 0; // total charge in Wh for the connected device

struct tm startTime;
struct tm endTime;


unsigned short VID = 0;
unsigned short PID = 0;

char str_num[20]; // char array used for float to char conversions

void set_charge_mode_Reset(void){
    // set usb charging mode to SDP - supports USB comms, 0.5A max
    USB_Charger_CTL1_SetLow();
    USB_Charger_CTL2_SetLow();
    USB_Charger_CTL3_SetLow();
}

void set_charge_mode_SDP(void){
    // set usb charging mode to SDP - supports USB comms, 0.5A max
    USB_Charger_CTL1_SetHigh();
    USB_Charger_CTL2_SetHigh();
    USB_Charger_CTL3_SetLow();
}

void set_charge_mode_CDP(void){
    // set usb charging mode to CDP - supports USB comms, 1.5A max
    USB_Charger_CTL1_SetHigh();
    USB_Charger_CTL2_SetHigh();
    USB_Charger_CTL3_SetHigh();
}

void set_charge_mode_DCP(void){
    // set usb charging mode to DCP - no USB comms, 1.5A max
    USB_Charger_CTL1_SetHigh();
    USB_Charger_CTL2_SetLow();
    USB_Charger_CTL3_SetHigh();
}

//******************************************************************************
//******************************************************************************
// USB Support Functions
//******************************************************************************
//******************************************************************************

/****************************************************************************
  Function:
    BOOL USB_ApplicationEventHandler( BYTE address, USB_EVENT event,
                void *data, DWORD size )

  Summary:
    This is the application event handler.  It is called when the stack has
    an event that needs to be handled by the application layer rather than
    by the client driver.

  Description:
    This is the application event handler.  It is called when the stack has
    an event that needs to be handled by the application layer rather than
    by the client driver.  If the application is able to handle the event, it
    returns TRUE.  Otherwise, it returns FALSE.

  Precondition:
    None

  Parameters:
    BYTE address    - Address of device where event occurred
    USB_EVENT event - Identifies the event that occured
    void *data      - Pointer to event-specific data
    DWORD size      - Size of the event-specific data

  Return Values:
    TRUE    - The event was handled
    FALSE   - The event was not handled

  Remarks:
    The application may also implement an event handling routine if it
    requires knowledge of events.  To do so, it must implement a routine that
    matches this function signature and define the USB_HOST_APP_EVENT_HANDLER
    macro as the name of that function.
  ***************************************************************************/

BOOL USB_ApplicationEventHandler( BYTE address, USB_EVENT event, void *data, DWORD size )
{
    switch( (int) event )
    {
        // --------------------------------------------------------------------------
        // Charger events

        case EVENT_CHARGER_ATTACH:
            //UART2PrintString( "Device attached for charging.\r\n" );

                       
            // turn on the green led to show a connected status
            LED_GREEN_SetHigh();
            DeviceStatus = true;

            // reset the total charge value to 0
            TotalCharge = 0;
            
            // set the start time from the RTC
            while(!RTCC_TimeGet(&startTime)){};
            endTime = startTime;
            // set the end time to be the same as the start time

            // update the active status causing a trigger event on the connected client
            //UpdateBluetoothActiveStatus(DeviceStatus);
            return TRUE;
            break;

        case EVENT_CHARGER_DETACH:
            //UART2PrintString( "Charging device detached\r\n" );
            LED_GREEN_SetLow();
            DeviceStatus = false;

            while(!RTCC_TimeGet(&endTime)){};

            UpdateBluetoothActiveStatus(DeviceStatus);
            return TRUE;
            break;

        // --------------------------------------------------------------------------
        // Host events

        case EVENT_VBUS_REQUEST_POWER:
            // The data pointer points to a byte that represents the amount of power
            // requested in mA, divided by two.  If the device wants too much power,
            // we reject it.
            //if (((USB_VBUS_POWER_EVENT_DATA*)data)->current <= (MAX_ALLOWED_CURRENT / 2))
            //{
                //UART2PrintString(  "Device requires " );
                //UART2PutDec( (unsigned char)((WORD)((USB_VBUS_POWER_EVENT_DATA*)data)->current * 2 / 10) );
                //UART2PutDec( (unsigned char)((WORD)((USB_VBUS_POWER_EVENT_DATA*)data)->current * 2 % 10) );
                //UART2PrintString(  "mA.\r\n" );
                return TRUE;
            //}
            //else
            //{
                //UART2PrintString(  "Device requires too much current.\r\n" );
            //}
            break;

        case EVENT_VBUS_RELEASE_POWER:
            // Turn off Vbus power.
            // The PIC24F with the Explorer 16 cannot turn off Vbus through software.
            return TRUE;
            break;

        case EVENT_HUB_ATTACH:
            //UART2PrintString(  "Hubs are not supported.\r\n" );
            return TRUE;
            break;

        case EVENT_UNSUPPORTED_DEVICE:
            LED_GREEN_SetHigh();
            //UART2PrintString(  "Device is not supported.\r\n" );
            return TRUE;
            break;

        case EVENT_CANNOT_ENUMERATE:
            LED_GREEN_SetHigh();
            //UART2PrintString(  "Cannot enumerate device.\r\n" );
            return TRUE;
            break;

        case EVENT_CLIENT_INIT_ERROR:
            //UART2PrintString(  "Client driver initialization error.\r\n" );
            return TRUE;
            break;

        case EVENT_OUT_OF_MEMORY:
            //UART2PrintString(  "Out of heap memory.\r\n" );
            return TRUE;
            break;

        case EVENT_UNSPECIFIED_ERROR:   // This should never be generated.
            //UART2PrintString( "Unspecified USB error.\r\n" );
            return TRUE;
            break;

        default:
            break;
    }

    return FALSE;
}



//******************************************************************************
//******************************************************************************
// Internal Functions
//******************************************************************************
//******************************************************************************

/****************************************************************************
  Function:
     void InitializeVbusMonitor( void )

  Description:
    This function initializes monitoring of the VBUS analog input.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/

void InitializeVbusMonitor( void )
{
   

    return;
}





//******************************************************************************
//******************************************************************************
//******************************************************************************
// Main
//******************************************************************************
//******************************************************************************
//******************************************************************************


/*
                         Main application
 */
int main(void)
{
    // initialize the device
    OSCILLATOR_Initialize();
    PIN_MANAGER_Initialize();
    
    LED_RED_SetHigh();
    
    INTERRUPT_Initialize();
    SDADC1_InitializeADC0();
    SDADC1_InitializeADC1();
    UART1_Initialize();
    EXT_INT_Initialize();
    initBluetooth();
    while (initBluetoothComplete == false){
    
    }
    RTCC_Initialize();

    // initialise the bluetooth module    

    // Initialize USB Embedded Host
    USBInitialize( 0 );

    // Turn on the A/D converter to monitor Vbus.
    InitializeVbusMonitor();
  
    Power_Enable_SetHigh();
    set_charge_mode_CDP();
    USB_Charger_Enable_SetHigh();

    // Set a default date and time
    struct tm Time;
    Time.tm_year = 15; // year
    Time.tm_mon = 1; // month
    Time.tm_mday = 1; // day
    Time.tm_wday = 4; // weekday
    Time.tm_hour = 1; // hour
    Time.tm_min = 1; // minute
    Time.tm_sec = 1; // second

    RTCC_TimeSet(&Time);

    
    startTime.tm_year = 15; // year
    startTime.tm_mon = 1; // month
    startTime.tm_mday = 1; // day
    startTime.tm_wday = 4; // weekday
    startTime.tm_hour = 1; // hour
    startTime.tm_min = 1; // minute
    startTime.tm_sec = 1; // second
    
    endTime.tm_year = 15; // year
    endTime.tm_mon = 1; // month
    endTime.tm_mday = 1; // day
    endTime.tm_wday = 4; // weekday
    endTime.tm_hour = 1; // hour
    endTime.tm_min = 1; // minute
    endTime.tm_sec = 1; // second
    
    while (1)
    {
        

        if (DoUpdate){

            USBTasks();

            CheckBluetoothValues();
            UpdateBluetoothValues();

            DoUpdate = false;

            Sleep();
        }



    }

    return -1;
}
/**
 End of File
*/