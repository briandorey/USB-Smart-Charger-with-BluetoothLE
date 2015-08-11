/* 
 * File:   functions.c
 * Author: andrew
 *
 * Created on 18 January 2015, 21:24
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "main.h"
#include "HardwareProfile.h"
#include <libpic30.h>
#include "mcc_generated_files/pin_manager.h"


double adc_voltage = 0;
long _powersof10[8] = {10000000, 1000000, 100000, 10000, 1000, 100, 10, 1};

// nthdigit returns an ASCII character for the nth position in a long, used for converting numbers to strings in place of sprintf
char nthdigit(long x, int n)
{
    static long powersof10[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000};
    return ((x / powersof10[n]) % 10) + '0';
}

// CharToInt combines two ASCII char values into an integer
unsigned int CharToInt(char high, char low){
    return (high - '0') * 0x10 + (low - '0');
}


double CharToDouble(char *array){
    double returnval = 0;

    int x = 0;
    for ( x = 0; x < 8; x++ ) {
        if (array[x] != 0){
            returnval += array[x] * _powersof10[x];
        }
    }

    return returnval / 1000;
}


double calculateInputVoltage(double rawval){
    //adc_voltage = rawval;
    adc_voltage = (0.0000152590219 * rawval) * 38.03; // multiply the raw adc value by the voltage reference
    return adc_voltage;
}

double tmp = 0;

void calculateUSBPower(double rawval){
    //adc_voltage = rawval;
    adc_voltage = (0.0000152590219 * rawval) * 6.815; // multiply the raw adc value by the voltage reference

    // get the power in watts
    CurrentPowerUsage = adc_voltage * 5;
    if (CurrentPowerUsage > 0){
        tmp = TotalCharge + (CurrentPowerUsage / 3600);
    }
    // update the total charge
    TotalCharge = tmp;
}



void blinkRed(void){
    LED_RED_SetHigh();
    __delay_ms(100);
    LED_RED_SetLow();
    __delay_ms(100);
}

void blinkGreen(void){
    LED_GREEN_SetHigh();
    __delay_ms(100);
    LED_GREEN_SetLow();
    __delay_ms(100);
}
