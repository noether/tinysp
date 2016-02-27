/* fonctions for simple LED manipulation               */
/* december 2004: first example for microinfo          */
/* by Francesco Mondada                                */
 
#include "e_epuck_ports.h"
#include "e_agenda.h"


/**
 * Set one or all LEDs to OFF or ON
 *
 * @param led_number	IN	ID of the LED (between 0 and 7)
 *							if not 0-7, all leds are set to value
 * @param value			IN	0 (off) or 1 (on)
 * @return void			OUT	not used
 */
void e_set_led(unsigned int led_number, unsigned int value)
// led_number between 0 and 7, value 0 (off) or 1 (on)
// if led_number other than 0-7, all leds are set to value
{
	switch(led_number)
	{
		case 0: 
			{
			if(value>1)
				LED0 = LED0^1;
			else
				LED0 = value;
			break;
			}
		case 1: 
			{
			if(value>1)
				LED1 = LED1^1;
			else
				LED1 = value;
			break;
			}
		case 2: 
			{
			if(value>1)
				LED2 = LED2^1;
			else
				LED2 = value;
			break;
			}
		case 3: 
			{
			if(value>1)
				LED3 = LED3^1;
			else
				LED3 = value;
			break;
			}
		case 4: 
			{
			if(value>1)
				LED4 = LED4^1;
			else
				LED4 = value;
			break;
			}
		case 5: 
			{
			if(value>1)
				LED5 = LED5^1;
			else
				LED5 = value;
			break;
			}
		case 6: 
			{
			if(value>1)
				LED6 = LED6^1;
			else
				LED6 = value;
			break;
			}
		case 7: 
			{
			if(value>1)
				LED7 = LED7^1;
			else
				LED7 = value;
			break;
			}
		default: 
			LED0 = LED1 = LED2 = LED3 = LED4 = LED5 = LED6 = LED7 = value;
	}
}

/**
 * Fonction to clear all LEDs
 *
 * @param void		IN	not used
 * @return void		OUT	not used
 */
void e_led_clear(void)
{
	LED0 = 0;
	LED1 = 0;
	LED2 = 0;
	LED3 = 0;
	LED4 = 0;
	LED5 = 0;
	LED6 = 0;
	LED7 = 0;
}

/**
 * Callback function for an agenda
 *
 * @param void		IN	not used
 * @return void		OUT	not used
 */
void e_blink_led(void)
{
	LED0 = ~LED0;
	LED1 = ~LED1;
	LED2 = ~LED2;
	LED3 = ~LED3;
	LED4 = ~LED4;
	LED5 = ~LED5;
	LED6 = ~LED6;
	LED7 = ~LED7;
}
/**
 * Start the blinking of all LED
 *
 * @param void		IN	not used
 * @return void		OUT	not used
 */
void e_start_led_blinking(int cycle)
{
  e_activate_agenda(e_blink_led, cycle);
}

/**
 * Stop the blinking of all LED
 *
 * @param void		IN	not used
 * @return void		OUT	not used
 */
void e_stop_led_blinking(void)
{
  e_destroy_agenda(e_blink_led);
}

void e_set_blinking_cycle(int cycle)
{
	if (cycle>=0)
		e_set_agenda_cycle(e_blink_led,cycle);
}

void e_blink_led0(void)
{
	LED0 = ~LED0;
}

void e_blink_led1(void)
{
	LED1 = ~LED1;
}

void e_blink_led2(void)
{
	LED2 = ~LED2;
}

void e_blink_led3(void)
{
	LED3 = ~LED3;
}

void e_blink_led4(void)
{
	LED4 = ~LED4;
}

void e_blink_led5(void)
{
	LED5 = ~LED5;
}

void e_blink_led6(void)
{
	LED6 = ~LED6;
}

void e_blink_led7(void)
{
	LED7 = ~LED7;
}


void e_set_body_led(unsigned int value)
{
	if(value>1)
		BODY_LED = BODY_LED^1;
	else
		BODY_LED = value;
}

void e_set_front_led(unsigned int value)
{
	if(value>1)
		FRONT_LED = FRONT_LED^1;
	else
	FRONT_LED = value;
}
