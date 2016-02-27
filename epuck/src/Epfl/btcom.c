#ifndef BTCOM_C
#define BTCOM_C

#include "btcom.h"

#include "e_uart_char.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Don't forget to initialize hardware before using it when debugging. Library to use on the e-puck
// maximum size of messages is set to 255 bytes


void btcomSendStringStatic (char* buffer)
{
    e_send_uart1_char(buffer, sizeof(*buffer) - 1);
    while(e_uart1_sending());  
}
	
void btcomSendString (char* buffer)
{
    e_send_uart1_char(buffer, strlen(buffer));
    while(e_uart1_sending());
}

void btcomSendInt (long int x)
{
    char msg[BTCOM_MAX_MESSAGE_LENGTH];
    sprintf (msg, "%ld", x);
    btcomSendString(msg);
} 

void btcomSendFloat (double x)
{
    char msg[BTCOM_MAX_MESSAGE_LENGTH];
    sprintf (msg, "%lf", x);
    btcomSendString(msg);
}	 
    
void btcomSendChar (char c)
{
    e_send_uart1_char(&c, 1);
    while(e_uart1_sending());    
}

unsigned char btcomReadChar(void)
{
    unsigned char msg;
    e_getchar_uart1(&msg);
    return msg;
}

void btcomWaitForCommand (char trigger)
{
    char msg;
    do
    {
	e_getchar_uart1 (&msg);
    }
    while (msg != trigger);
    
    // sleep a bit
    long int count;
    for(count = 0; count < 1000000; count++) 
	asm("nop");
}

// BTCOM_C
#endif
