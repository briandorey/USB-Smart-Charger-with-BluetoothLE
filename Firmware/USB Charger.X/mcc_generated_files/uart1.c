/**
  UART1 Generated Driver File 

  @Company
    Microchip Technology Inc.

  @File Name
    uart1.c

  @Summary
    This is the generated source file for the UART1 driver using MPLAB® Code Configurator

  @Description
    This source file provides APIs for driver for UART1. 
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

#include "uart1.h"
#include <stdlib.h>
#include <string.h>
#include "pin_manager.h"
#include "../HardwareProfile.h"
#include "../bluetooth.h"
#include <libpic30.h>



/**
  Section: Data Type Definitions
*/

bool UART_NEWLINE_RECEIVED = false;
unsigned char UART_CURRENT_BYTE = 0;
int UART_TIMEOUT = 5000;

/** UART Driver Queue Status

  @Summary
    Defines the object required for the status of the queue.
*/



typedef union
{
    struct
    {
            uint8_t full:1;
            uint8_t empty:1;
            uint8_t reserved:6;
    }s;
    uint8_t status;
}

UART_BYTEQ_STATUS;

/** UART Driver Hardware Instance Object

  @Summary
    Defines the object required for the maintenance of the hardware instance.

*/
typedef struct
{   

    /* TX Byte Q */
    uint8_t                                      *txTail ;

    uint8_t                                      *txHead ;   

    UART_BYTEQ_STATUS                        txStatus ;

} UART_OBJECT ;

static UART_OBJECT uart1_obj ;

/** UART Driver Queue Length

  @Summary
    Defines the length of the Transmit and Receive Buffers

*/

#define UART1_CONFIG_TX_BYTEQ_LENGTH 48
#define UART1_CONFIG_RX_BYTEQ_LENGTH 48


/** UART Driver Queue

  @Summary
    Defines the Transmit and Receive Buffers

*/

static uint8_t uart1_txByteQ[UART1_CONFIG_TX_BYTEQ_LENGTH] ;

uint8_t uart1_rxBuffer[48];
uint8_t uart1_rxPosition = 0;
uint8_t uart1_rxLength = 0;
bool uart1_rxBufferFull = false;

/** UART Hardware FIFO Buffer Length

  @Summary
    Defines the length of the Transmit and Receive FIFOs
 
*/

#define UART1_TX_FIFO_LENGTH 1
#define UART1_RX_FIFO_LENGTH 1 

/**
  Section: Driver Interface
*/


void UART1_Initialize (void)
{
   // RTSMD enabled; URXINV disabled; BRGH enabled; STSEL 1; UARTEN enabled; PDSEL 8N; LPBACK disabled; WAKE disabled; USIDL disabled; ABAUD disabled; IREN disabled; UEN TX_RX; 
   U1MODE = 0x8808;
   // UTXEN disabled; UTXINV disabled; URXISEL RX_ONE_CHAR; ADDEN disabled; UTXISEL0 TX_ONE_CHAR; UTXBRK COMPLETED; OERR NO_ERROR_cleared; 
   U1STA = 0x0000;
   // U1TXREG 0x0000; 
   U1TXREG = 0x0000;
   // U1RXREG 0x0000; 
   U1RXREG = 0x0000;
   // Baud Rate = 115200; BRG 34; 
   U1BRG = 0x0022;

   IEC0bits.U1RXIE = 1;

   U1STAbits.UTXEN = 1;

   uart1_obj.txHead = uart1_txByteQ;
   uart1_obj.txTail = uart1_txByteQ;
   uart1_obj.txStatus.s.empty = true;
   uart1_obj.txStatus.s.full = false;

   uart1_rxPosition = 0;
   uart1_rxLength = 0;
   uart1_rxBufferFull = false;
   
}

/**
    Maintains the driver's transmitter state machine and implements its ISR
*/
void __attribute__ ( ( interrupt, no_auto_psv ) ) _U1TXInterrupt ( void )
{ 
    if(uart1_obj.txStatus.s.empty)
    {
        IEC0bits.U1TXIE = false;
        return;
    }

    IFS0bits.U1TXIF = false;

    int count = 0;
    while((count < UART1_TX_FIFO_LENGTH)&& !(U1STAbits.UTXBF == 1))
    {
        count++;

        U1TXREG = *uart1_obj.txHead;

        uart1_obj.txHead++;

        if(uart1_obj.txHead == (uart1_txByteQ + UART1_CONFIG_TX_BYTEQ_LENGTH))
        {
            uart1_obj.txHead = uart1_txByteQ;
        }

        uart1_obj.txStatus.s.full = false;

        if(uart1_obj.txHead == uart1_obj.txTail)
        {
            uart1_obj.txStatus.s.empty = true;
            break;
        }
    }
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _U1RXInterrupt( void )
{
    int count = 0;

    while((count < UART1_RX_FIFO_LENGTH) && (U1STAbits.URXDA == 1))
    {
        count++;

        UART_CURRENT_BYTE = U1RXREG;

        uart1_rxBuffer[uart1_rxPosition] = UART_CURRENT_BYTE;
        uart1_rxPosition++;
        uart1_rxLength ++;
        
        if(uart1_rxLength == UART1_CONFIG_RX_BYTEQ_LENGTH)
        {
            //Sets the flag RX full
            uart1_rxBufferFull = true;
            break;
        }
        
    }
    // check for new line character

    if (UART_CURRENT_BYTE == '\n' ){
        UART_NEWLINE_RECEIVED = true;      
        uart1_rxPosition = 0;
    }
    IFS0bits.U1RXIF = false;
   
}


void __attribute__ ( ( interrupt, no_auto_psv ) ) _U1ErrInterrupt ( void )
{
    if ((U1STAbits.OERR == 1))
    {
        U1STAbits.OERR = 0;
    }

    IFS4bits.U1ERIF = false;
}

/**
  Section: UART Driver Client Routines
*/

void UART1_ResetBuffer(void)
{
    UART_NEWLINE_RECEIVED = false;
    uart1_rxPosition = 0;
    uart1_rxLength = 0;
}

void UART1_Write( const uint8_t byte)
{
    *uart1_obj.txTail = byte;

    uart1_obj.txTail++;
    
    if (uart1_obj.txTail == (uart1_txByteQ + UART1_CONFIG_TX_BYTEQ_LENGTH))
    {
        uart1_obj.txTail = uart1_txByteQ;
    }

    uart1_obj.txStatus.s.empty = false;

    if (uart1_obj.txHead == uart1_obj.txTail)
    {
        uart1_obj.txStatus.s.full = true;
    }

    if (IEC0bits.U1TXIE  == false)
    {
        IEC0bits.U1TXIE = true ;
    }
	
}

unsigned int UART1_WriteBuffer( const uint8_t *buffer , const unsigned int bufLen )
{
    unsigned int numBytesWritten = 0 ;

    while ( numBytesWritten < ( bufLen ))
    {
        if((uart1_obj.txStatus.s.full))
        {
            break;
        }
        else
        {
            UART1_Write (buffer[numBytesWritten++] ) ;
        }
    }

    return numBytesWritten ;

}

UART1_TRANSFER_STATUS UART1_TransferStatusGet (void )
{
    UART1_TRANSFER_STATUS status = 0;

    if(uart1_obj.txStatus.s.full)
    {
        status |= UART1_TRANSFER_STATUS_TX_FULL;
    }

    if(uart1_obj.txStatus.s.empty)
    {
        status |= UART1_TRANSFER_STATUS_TX_EMPTY;
    }    
    
    return status;
}


unsigned int UART1_TransmitBufferSizeGet(void)
{
    if(!uart1_obj.txStatus.s.full)
    { 
        if(uart1_obj.txHead > uart1_obj.txTail)
        {
            return(UART1_CONFIG_TX_BYTEQ_LENGTH - (uart1_obj.txHead - uart1_obj.txTail));
        }
        else
        {
            return(UART1_CONFIG_TX_BYTEQ_LENGTH - (uart1_obj.txTail - uart1_obj.txHead));
        }
    }
    return 0;
}


bool UART1_TransmitBufferIsFull(void)
{
    return(uart1_obj.txStatus.s.full);
}

UART1_STATUS UART1_StatusGet (void)
{
    return U1STA;
}

void UART1_WriteString(const uint8_t *writeBuffer){

     int  writebufferLen = strlen((char *)writeBuffer);

     UART1_WriteBuffer ( writeBuffer, writebufferLen)  ;
     while(!(UART1_StatusGet() & UART1_TX_COMPLETE ))
        {
           // Wait for the tranmission to complete
        }
     UART1_Write('\r');
     while(!(UART1_StatusGet() & UART1_TX_COMPLETE ))
        {
           // Wait for the tranmission to complete
        }    


}

void WaitForNewLine(void){
    int loopcount = 0;

    while (!UART_NEWLINE_RECEIVED){
        if (UART_TIMEOUT == loopcount){
            LED_RED_SetHigh();
            break;
        }
        __delay_ms(1);
        loopcount++;
    }

    UART_NEWLINE_RECEIVED = false;

}

bool WaitForOK(void){
 /*   int loopcount = 0;

    // wait for a new line character
    while (!UART_NEWLINE_RECEIVED){
        if (UART_TIMEOUT == loopcount){
            LED_RED_SetHigh();
            return false;
        }
        __delay_ms(1);
        loopcount++;
    }
    // new line received so reset new line and read the buffer

    UART_NEWLINE_RECEIVED = false;

   
    if (bufferlength < 3){
        return false;
    }

    // check for the AOK command
    UART1_ReadBuffer(receivedBuffer, bufferlength);

    if (receivedBuffer[0] == 'A' && receivedBuffer[1] == 'O' && receivedBuffer[2] == 'K'){
        return true;
    }
    else{
        return false;
    }*/
    return true;
}
/**
  End of File
*/
