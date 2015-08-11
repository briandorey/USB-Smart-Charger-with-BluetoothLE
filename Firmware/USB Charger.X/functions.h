/* 
 * File:   functions.h
 * Author: andrew
 *
 * Created on 18 January 2015, 21:24
 */

extern long powersof10[8];

char nthdigit(long x, int n);

unsigned int CharToInt(char high, char low);

double CharToDouble(char *array);

char *doubleToChar(double val);

double calculateInputVoltage(double rawval);

void calculateUSBPower(double rawval);

void blinkRed(void);

void blinkGreen(void);
