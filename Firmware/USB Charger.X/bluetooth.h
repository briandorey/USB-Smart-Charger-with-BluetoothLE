/* 
 * File:   bluetooth.h
 * Author: andrew
 *
 * Created on 01 January 2015, 13:35
 */

extern bool initBluetoothComplete;

void initBluetooth(void);

void BluetoothTasks(void);
void UpdateBluetoothValues(void);
void UpdateBluetoothActiveStatus(bool Status);
void CheckBluetoothValues(void);