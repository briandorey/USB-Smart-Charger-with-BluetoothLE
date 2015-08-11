/* 
 * File:   main.h
 * Author: andrew
 *
 * Created on 22 June 2015, 11:10
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "GenericTypeDefs.h"

// variables
extern BOOL overcurrentStateUSB;        // We really only need a bit here.
extern BOOL DeviceStatus;  // show if a device is connected
extern BOOL IsSleeping; // used to record if the device is in a sleep state

extern BOOL DoUpdate;

extern unsigned short VID;
extern unsigned short PID;

extern double CurrentPowerUsage; // current power usage for the connected device
extern double PowerDownVoltage; // voltage at which the charger will go to sleep
extern double PowerUpVoltage; // voltage at which the charger will wake from sleep
extern double TotalCharge; // total charge in Wh for the connected device

extern struct tm startTime;
extern struct tm endTime;

extern char str_num[20]; // char array used for float to char conversions

