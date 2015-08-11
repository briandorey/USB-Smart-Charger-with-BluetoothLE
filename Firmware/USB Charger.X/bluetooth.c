/*
 * File:   bluetooth.c
 * Author: andrew
 *
 * Created on 01 January 2015, 12:11
 */

#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "HardwareProfile.h"
#include "functions.h"
#include "mcc_generated_files/uart1.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/rtcc.h"
#include <libpic30.h>

/*
 *
 */

/** Bluetooth Initialisation

  @Summary
    Initialises the bluetooth module and sets up the GATT profile

 */

bool initBluetoothComplete = false;

bool firstRun = true;

double tempDouble = 0;
long tempLong = 0;
unsigned char PowerUsageResponse[] = "SHW,001A,00000000";
unsigned char TotalChargeResponse[] = "SHW,0026,00000000";
unsigned char PowerDownVoltageResponse[] = "SHW,001E,00000000";
unsigned char PowerUpVoltageResponse[] = "SHW,0020,00000000";
unsigned char DateTimeResponse[] = "SHW,0018,000000000000";
unsigned char VIDPIDResponse[] = "SHW,0022,0000000000";
unsigned char StartTimeResponse[] = "SHW,0024,000000000000";
unsigned char EndTimeResponse[] = "SHW,0028,000000000000";

unsigned char LastDate[12];

unsigned int x = 0;

struct tm Time;

void initBluetooth(void) {

    // initialise the bluetooth module
    BT_WAKE_HW_SetLow();
    __delay_ms(10);
    // enable the bluetooth module
    BT_WAKE_HW_SetHigh();
    __delay_ms(10);
    // enter command mode
    BT_Wake_SW_SetHigh();
    __delay_ms(10);
    BT_CMD_SetLow();

    WaitForNewLine();

    UART1_WriteString((unsigned char *) "SF,2"); // reset the device to factory defaults
    WaitForNewLine();

    UART1_WriteString((unsigned char *) "SN,Charger"); // set the device name
    WaitForNewLine();

    UART1_WriteString((unsigned char *) "SDN,Apexweb"); // set the manufacturer
    WaitForNewLine();

    UART1_WriteString((unsigned char *) "SDF,1.0"); // set the firmware revision
    WaitForNewLine();

    UART1_WriteString((unsigned char *) "SDH,1.0"); // set the hardware revision
    WaitForNewLine();

    UART1_WriteString((unsigned char *) "SDF,USB-Charger"); // set the model name
    WaitForNewLine();

    UART1_WriteString((unsigned char *) "SDR,1.0"); // set the software revision
    WaitForNewLine();

    UART1_WriteString((unsigned char *) "SDS,0001"); // set the serial number
    WaitForNewLine();

    UART1_WriteString((unsigned char *) "SS,80000001"); // set GATT profiles for Device Information and User Defined Private Services
    WaitForNewLine();

    UART1_WriteString((unsigned char *) "SR,24004000"); // set device as peripheral with automatic advertisement.
    WaitForNewLine();

    // Define private services

    // Date and Time:  Permissions: Read / Write   Size:12 bytes   Format:YYMMDDHHMMSS  ID: 0018
    UART1_WriteString((unsigned char *) "PS,AFF25C609CB411E4A1EB0002A5D5C51B");
    WaitForNewLine();
    UART1_WriteString((unsigned char *) "PC,AFF25C609CB411E4A1EB0002A5D5C51B,0A,12");
    WaitForNewLine();

    // Power Usage in Watts:  Permissions: Read   Size:8 bytes   Format:float Example 0023.56  ID: 001A
    UART1_WriteString((unsigned char *) "PS,C8CECD409CB411E48C610002A5D5C51B");
    WaitForNewLine();
    UART1_WriteString((unsigned char *) "PC,C8CECD409CB411E48C610002A5D5C51B,02,08");
    WaitForNewLine();

    // Charger Active:  Permissions: Read / Write   Size:1 byte   Format: Boolean  ID: 001C   001C
    UART1_WriteString((unsigned char *) "PS,D72DB2209CB411E4B9C50002A5D5C51B");
    WaitForNewLine();
    UART1_WriteString((unsigned char *) "PC,D72DB2209CB411E4B9C50002A5D5C51B,0A,01");
    WaitForNewLine();

    // Power Down Voltage:  Permissions: Read / Write   Size:8 bytes   Format: float Example: 12.2  ID: 001E
    UART1_WriteString((unsigned char *) "PS,E7D379C09CB411E4BB320002A5D5C51B");
    WaitForNewLine();
    UART1_WriteString((unsigned char *) "PC,E7D379C09CB411E4BB320002A5D5C51B,0A,08");
    WaitForNewLine();

    // Power Up Voltage:  Permissions: Read / Write   Size:8 bytes   Format: float Example: 12.6  ID: 0020
    UART1_WriteString((unsigned char *) "PS,F60004009CB411E4B7C90002A5D5C51B");
    WaitForNewLine();
    UART1_WriteString((unsigned char *) "PC,F60004009CB411E4B7C90002A5D5C51B,0A,08");
    WaitForNewLine();

    // Charging Device VID/PID:  Permissions: Read   Size:4 bytes   Format: uint32  ID: 0022
    UART1_WriteString((unsigned char *) "PS,02B09CA09CB511E4BC170002A5D5C51B");
    WaitForNewLine();
    UART1_WriteString((unsigned char *) "PC,02B09CA09CB511E4BC170002A5D5C51B,02,10");
    WaitForNewLine();

    // Charging Device Start Time:  Permissions: Read   Size:12 bytes   Format:YYMMDDHHMMSS  ID: 0024
    UART1_WriteString((unsigned char *) "PS,0FF845209CB511E481C40002A5D5C51B");
    WaitForNewLine();
    UART1_WriteString((unsigned char *) "PC,0FF845209CB511E481C40002A5D5C51B,02,12");
    WaitForNewLine();

    // Charging Device Total Charge (Wh):  Permissions: Read   Size:8 bytes   Format:float Example 0423.56  ID: 0026
    UART1_WriteString((unsigned char *) "PS,21351CA09CB511E48B450002A5D5C51B");
    WaitForNewLine();
    UART1_WriteString((unsigned char *) "PC,21351CA09CB511E48B450002A5D5C51B,02,08");
    WaitForNewLine();

    // Charging Device End Time:  Permissions: Read   Size:12 bytes   Format:YYMMDDHHMMSS  ID: 0028
    UART1_WriteString((unsigned char *) "PS,5281A8009CB511E4BE290002A5D5C51B");
    WaitForNewLine();
    UART1_WriteString((unsigned char *) "PC,5281A8009CB511E4BE290002A5D5C51B,02,12");
    WaitForNewLine();



    // Priavte services defined, reboot the device to initialise the changes

    UART1_WriteString((unsigned char *) "R,1");
    WaitForNewLine();
    WaitForNewLine();

    // Blink the green led 3 times to show the charger is initialised
    LED_RED_SetLow();
    blinkGreen();
    blinkGreen();
    blinkGreen();
    initBluetoothComplete = true;
}

void UpdateBluetoothValues(void) {
    // set the date and time

    while (!RTCC_TimeGet(&Time)) {
    };

    DateTimeResponse[9] = (unsigned char) nthdigit(Time.tm_year, 1);
    DateTimeResponse[10] = (unsigned char) nthdigit(Time.tm_year, 0);

    DateTimeResponse[11] = (unsigned char) nthdigit(Time.tm_mon, 1);
    DateTimeResponse[12] = (unsigned char) nthdigit(Time.tm_mon, 0);

    DateTimeResponse[13] = (unsigned char) nthdigit(Time.tm_mday, 1);
    DateTimeResponse[14] = (unsigned char) nthdigit(Time.tm_mday, 0);

    DateTimeResponse[15] = (unsigned char) nthdigit(Time.tm_hour, 1);
    DateTimeResponse[16] = (unsigned char) nthdigit(Time.tm_hour, 0);

    DateTimeResponse[17] = (unsigned char) nthdigit(Time.tm_min, 1);
    DateTimeResponse[18] = (unsigned char) nthdigit(Time.tm_min, 0);

    DateTimeResponse[19] = (unsigned char) nthdigit(Time.tm_sec, 1);
    DateTimeResponse[20] = (unsigned char) nthdigit(Time.tm_sec, 0);


    //LastDate[x] = DateTimeResponse[x + 9];


    UART1_WriteString((unsigned char *) DateTimeResponse);

    __delay_ms(1);

    // get the current power usage from the ADC

    if (CurrentPowerUsage > 0) {
        tempDouble = CurrentPowerUsage * 1000;
        tempLong = (long) tempDouble;
    } else {
        tempLong = 0;
    }

    PowerUsageResponse[9] = nthdigit(tempLong, 7);
    PowerUsageResponse[10] = nthdigit(tempLong, 6);
    PowerUsageResponse[11] = nthdigit(tempLong, 5);
    PowerUsageResponse[12] = nthdigit(tempLong, 4);
    PowerUsageResponse[13] = nthdigit(tempLong, 3);
    PowerUsageResponse[14] = nthdigit(tempLong, 2);
    PowerUsageResponse[15] = nthdigit(tempLong, 1);
    PowerUsageResponse[16] = nthdigit(tempLong, 0);

    UART1_WriteString(PowerUsageResponse);

    __delay_ms(1);

    // check to see if the charger is currently active
    if (Power_Enable_GetValue() == 1) {
        UART1_WriteString((unsigned char *) "SHW,001C,01");
    } else {
        UART1_WriteString((unsigned char *) "SHW,001C,00");
    }

    __delay_ms(1);

    // Return the current power down voltage

    if (PowerDownVoltage > 0) {
        tempDouble = PowerDownVoltage * 1000;
        tempLong = (long) tempDouble;
    } else {
        tempLong = 0;
    }

    PowerDownVoltageResponse[9] = nthdigit(tempLong, 7);
    PowerDownVoltageResponse[10] = nthdigit(tempLong, 6);
    PowerDownVoltageResponse[11] = nthdigit(tempLong, 5);
    PowerDownVoltageResponse[12] = nthdigit(tempLong, 4);
    PowerDownVoltageResponse[13] = nthdigit(tempLong, 3);
    PowerDownVoltageResponse[14] = nthdigit(tempLong, 2);
    PowerDownVoltageResponse[15] = nthdigit(tempLong, 1);
    PowerDownVoltageResponse[16] = nthdigit(tempLong, 0);

    UART1_WriteString(PowerDownVoltageResponse);

    __delay_ms(1);

    // Power Up Voltage - float - 8 bytes
    // Return the current power up voltage

    if (PowerDownVoltage > 0) {
        tempDouble = PowerUpVoltage * 1000;
        tempLong = (long) tempDouble;

    } else {
        tempLong = 0;
    }

    PowerUpVoltageResponse[9] = nthdigit(tempLong, 7);
    PowerUpVoltageResponse[10] = nthdigit(tempLong, 6);
    PowerUpVoltageResponse[11] = nthdigit(tempLong, 5);
    PowerUpVoltageResponse[12] = nthdigit(tempLong, 4);
    PowerUpVoltageResponse[13] = nthdigit(tempLong, 3);
    PowerUpVoltageResponse[14] = nthdigit(tempLong, 2);
    PowerUpVoltageResponse[15] = nthdigit(tempLong, 1);
    PowerUpVoltageResponse[16] = nthdigit(tempLong, 0);

    UART1_WriteString(PowerUpVoltageResponse);

    __delay_ms(1);

    // Charging Device VID/PID  - uint32 - 4 bytes
    // return the VID and PID of the connected or last USB device

    VIDPIDResponse[9] = nthdigit(VID, 4);
    VIDPIDResponse[10] = nthdigit(VID, 3);
    VIDPIDResponse[11] = nthdigit(VID, 2);
    VIDPIDResponse[12] = nthdigit(VID, 1);
    VIDPIDResponse[13] = nthdigit(VID, 0);

    VIDPIDResponse[14] = nthdigit(PID, 4);
    VIDPIDResponse[15] = nthdigit(PID, 3);
    VIDPIDResponse[16] = nthdigit(PID, 2);
    VIDPIDResponse[17] = nthdigit(PID, 1);
    VIDPIDResponse[18] = nthdigit(PID, 0);

    UART1_WriteString((unsigned char *) VIDPIDResponse);

    __delay_ms(1);
    // Charging Device Start Time YYMMDDHHmmSS - 6 bytes
    // return the date and time of the charging start time


    StartTimeResponse[9] = (unsigned char) nthdigit(startTime.tm_year, 1);
    StartTimeResponse[10] = (unsigned char) nthdigit(startTime.tm_year, 0);

    StartTimeResponse[11] = (unsigned char) nthdigit(startTime.tm_mon, 1);
    StartTimeResponse[12] = (unsigned char) nthdigit(startTime.tm_mon, 0);

    StartTimeResponse[13] = (unsigned char) nthdigit(startTime.tm_mday, 1);
    StartTimeResponse[14] = (unsigned char) nthdigit(startTime.tm_mday, 0);

    StartTimeResponse[15] = (unsigned char) nthdigit(startTime.tm_hour, 1);
    StartTimeResponse[16] = (unsigned char) nthdigit(startTime.tm_hour, 0);

    StartTimeResponse[17] = (unsigned char) nthdigit(startTime.tm_min, 1);
    StartTimeResponse[18] = (unsigned char) nthdigit(startTime.tm_min, 0);

    StartTimeResponse[19] = (unsigned char) nthdigit(startTime.tm_sec, 1);
    StartTimeResponse[20] = (unsigned char) nthdigit(startTime.tm_sec, 0);

    UART1_WriteString((unsigned char *) StartTimeResponse);

    __delay_ms(1);
    // Charging Device Total Charge (Wh) - float - 7 bytes
    // return the total charge power for the current or last connected device


    if (TotalCharge > 0) {
        tempDouble = TotalCharge * 1000;
        tempLong = (long) tempDouble;
    } else {
        tempLong = 0;
    }
    TotalChargeResponse[9] = nthdigit(tempLong, 7);
    TotalChargeResponse[10] = nthdigit(tempLong, 6);
    TotalChargeResponse[11] = nthdigit(tempLong, 5);
    TotalChargeResponse[12] = nthdigit(tempLong, 4);
    TotalChargeResponse[13] = nthdigit(tempLong, 3);
    TotalChargeResponse[14] = nthdigit(tempLong, 2);
    TotalChargeResponse[15] = nthdigit(tempLong, 1);
    TotalChargeResponse[16] = nthdigit(tempLong, 0);

    UART1_WriteString(TotalChargeResponse);

    __delay_ms(1);
    // Charging Device End Time YYMMDDHHmmSS - 6 bytes
    // return the date and time of the charging end time
    // return now if the device is still charging


    EndTimeResponse[9] = (unsigned char) nthdigit(endTime.tm_year, 1);
    EndTimeResponse[10] = (unsigned char) nthdigit(endTime.tm_year, 0);

    EndTimeResponse[11] = (unsigned char) nthdigit(endTime.tm_mon, 1);
    EndTimeResponse[12] = (unsigned char) nthdigit(endTime.tm_mon, 0);

    EndTimeResponse[13] = (unsigned char) nthdigit(endTime.tm_mday, 1);
    EndTimeResponse[14] = (unsigned char) nthdigit(endTime.tm_mday, 0);

    EndTimeResponse[15] = (unsigned char) nthdigit(endTime.tm_hour, 1);
    EndTimeResponse[16] = (unsigned char) nthdigit(endTime.tm_hour, 0);

    EndTimeResponse[17] = (unsigned char) nthdigit(endTime.tm_min, 1);
    EndTimeResponse[18] = (unsigned char) nthdigit(endTime.tm_min, 0);

    EndTimeResponse[19] = (unsigned char) nthdigit(endTime.tm_sec, 1);
    EndTimeResponse[20] = (unsigned char) nthdigit(endTime.tm_sec, 0);

    UART1_WriteString((unsigned char *) EndTimeResponse);

    firstRun = false;
}

bool DataMatch = true;

void CheckBluetoothValues(void) {
    if (!firstRun) {

        // Reset the UART RX buffer to clear it
        UART1_ResetBuffer();


        DataMatch = true;
        // Check RTC value
        UART1_WriteString((unsigned char *) "SHR,0018");

        __delay_ms(5);

        // check if a recevied command is in the buffer
        if (uart1_rxLength > 11) {
            // check if the date in the Bluetooth module matches the LastDate variable.  If not then the date has been updated by a client
            for (x = 0; x < 10; x++) {
                if (DateTimeResponse[x + 9] != uart1_rxBuffer[x]) {
                    DataMatch = false;
                }
            }

            if (DataMatch == false) {
                if ((uart1_rxBuffer[0] == '1' || uart1_rxBuffer[0] == '2') && ((uart1_rxBuffer[1] >= '0') && (uart1_rxBuffer[1] <= '9'))){
                    Time.tm_year = CharToInt(uart1_rxBuffer[0], uart1_rxBuffer[1]);
                    Time.tm_mon = CharToInt(uart1_rxBuffer[2], uart1_rxBuffer[3]);
                    Time.tm_mday = CharToInt(uart1_rxBuffer[4], uart1_rxBuffer[5]);
                    Time.tm_hour = CharToInt(uart1_rxBuffer[6], uart1_rxBuffer[7]);
                    Time.tm_min = CharToInt(uart1_rxBuffer[8], uart1_rxBuffer[9]);
                    Time.tm_sec = CharToInt(uart1_rxBuffer[10], uart1_rxBuffer[11]);
                    Time.tm_wday = 1; // weekday
                    RTCC_TimeSet(&Time);

                    blinkRed();
                }
            }

        }

    }

    // Check Alert Status
}

/*
void BluetoothTasks(void) {
    unsigned int bufferlength = UART1_ReceiveBufferSizeGet();
    unsigned char receivedBuffer[bufferlength];

    UART1_ReadBuffer(receivedBuffer, bufferlength);

    if (initBluetoothComplete) {

        if (receivedBuffer[0] == 'W' && receivedBuffer[1] == 'V') {
            // request data command received


            if (receivedBuffer[5] == '1' && receivedBuffer[6] == '8') { // Date and Time YYMMDDHHmmSS - 12 bytes
                // set the system date and time from the RTC
                struct tm Time;

                Time.tm_year = CharToInt(receivedBuffer[8], receivedBuffer[9]);
                Time.tm_mon = CharToInt(receivedBuffer[10], receivedBuffer[11]);
                Time.tm_mday = CharToInt(receivedBuffer[12], receivedBuffer[13]);
                Time.tm_hour = CharToInt(receivedBuffer[14], receivedBuffer[15]);
                Time.tm_min = CharToInt(receivedBuffer[16], receivedBuffer[17]);
                Time.tm_sec = CharToInt(receivedBuffer[18], receivedBuffer[19]);
                Time.tm_wday = 1; // weekday
                RTCC_TimeSet(&Time);
            }

            if (receivedBuffer[5] == '1' && receivedBuffer[6] == 'C') { // Set Active Status
                if (receivedBuffer[8] == '1') {
                    Power_Enable_SetHigh();
                } else {
                    Power_Enable_SetLow();
                }
            } else if (receivedBuffer[5] == '1' && receivedBuffer[6] == 'E') { // Power Down Voltage - float - 8 bytes
                // Set the current power down voltage
                char value[8] = {0, 0, 0, 0, 0, 0, 0, 0};
                int x = 0;
                unsigned char y = 0;
                for (x = 0; x < 8; x++) {
                    if (receivedBuffer[x + 8] != NULL) {
                        y = receivedBuffer[x + 8] - '0';
                        if (y >= 0 && y < 10) {
                            value[x] = y;
                        } else {
                            value[x] = 0;
                        }
                    }
                }

                PowerDownVoltage = CharToDouble(value);

            } else if (receivedBuffer[5] == '2' && receivedBuffer[6] == '0') { // Power Up Voltage - float - 8 bytes
                // Set the current power up voltage
                char value[8] = {0, 0, 0, 0, 0, 0, 0, 0};
                int x = 0;
                unsigned char y = 0;
                for (x = 0; x < 8; x++) {
                    if (receivedBuffer[x + 8] != NULL) {
                        y = receivedBuffer[x + 8] - '0';
                        if (y >= 0 && y < 10) {
                            value[x] = y;
                        } else {
                            value[x] = 0;
                        }
                    }
                }

                PowerUpVoltage = CharToDouble(value);
            }
        }

    }

}
 */
void UpdateBluetoothActiveStatus(bool Status) {
    if (Status) {
        UART1_WriteString((unsigned char *) "SHW,001C,01");
    } else {
        UART1_WriteString((unsigned char *) "SHW,001C,00");
    }
}