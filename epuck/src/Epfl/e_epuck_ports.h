/**************************************************************************
* 			Defintition of all port of e-puck 	 	  *
*			Version 1.0 november 2005			  *
*			Michael Bonani, Francesco Mondada, Davis Dadie    *
*									  *
**************************************************************************/

#ifndef _EPUCK_PORTS
#define _EPUCK_PORTS

#include "p30f6014a.h"

/*********************GENERAL SETUP************************/

#define FOSC   7.3728e6     // 7.3728Mhz crystal in XTL mode 
#define PLL    8.0       	// 8x PLL
 

#define FCY     ((FOSC*PLL)/(4.0))	// Instruction cycle frequency 
#define MILLISEC  (FCY/1.0e3)		// 1mSec delay constant
#define MICROSEC  (FCY/1.0e6)		// 1uSec delay constant
#define NANOSEC   (FCY/1.0e9)		// 1nSec delay constant

#define	TCY_PIC		(1e9/FCY)		//time instruction cycle in [ns] 
#define	INTERRUPT_DELAY	(10*TCY_PIC)//delay to start an interrupt in [ns] (observe with p30f6014) 

#define TRUE	1
#define FALSE	0


/********************** OUTPUTS ***************************/
#define OUTPUT_PIN 0 
/*LEDS*/
/*First in front of robot than turning clokwise*/
#define LED0 _LATA6
#define LED1 _LATA7
#define LED2 _LATA9
#define LED3 _LATA12
#define LED4 _LATA10
#define LED5 _LATA13
#define LED6 _LATA14
#define LED7 _LATA15

#define LED0_DIR _TRISA6
#define LED1_DIR _TRISA7
#define LED2_DIR _TRISA9
#define LED3_DIR _TRISA12
#define LED4_DIR _TRISA10
#define LED5_DIR _TRISA13
#define LED6_DIR _TRISA14
#define LED7_DIR _TRISA15

#define FRONT_LED _LATC1
#define FRONT_LED_DIR _TRISC1

#define BODY_LED _LATC2
#define BODY_LED_DIR _TRISC2

/*IR*/
#define PULSE_IR0 _LATF7		// pulse IR 0 and 4
#define PULSE_IR1 _LATF8		// pulse IR 1 and 5
#define PULSE_IR2 _LATG0		// pulse IR 2 and 6
#define PULSE_IR3 _LATG1		// pulse IR 3 and 7

#define PULSE_IR0_DIR _TRISF7
#define PULSE_IR1_DIR _TRISF8
#define PULSE_IR2_DIR _TRISG0
#define PULSE_IR3_DIR _TRISG1

/*First in front right of robot than turning clokwise*/
#define IR0 8  // ir proximity sensor 0 on AD channel 8
#define IR1 9  // ir proximity sensor 1 on AD channel 9
#define IR2 10  // ir proximity sensor 2 on AD channel 10
#define IR3 11  // ir proximity sensor 3 on AD channel 11
#define IR4 12  // ir proximity sensor 4 on AD channel 12
#define IR5 13  // ir proximity sensor 5 on AD channel 13
#define IR6 14  // ir proximity sensor 6 on AD channel 14
#define IR7 15  // ir proximity sensor 7 on AD channel 15


/*analog*/
#define MIC1 2  // microphone 1 on AD channel 2
#define MIC2 3  // microphone 2 on AD channel 3
#define MIC3 4  // microphone 3 on AD channel 4


#define ACCX 5  // X Axis of accelerometer on AD channel 5
#define ACCY 6  // Y Axis of accelerometer on AD channel 6
#define ACCZ 7  // Z Axis of accelerometer on AD channel 7


/*basic audio*/
#define AUDIO_ON _LATF0
#define AUDIO_ON_DIR _TRISF0

/*motors*/
#define MOTOR1_PHA _LATD0
#define MOTOR1_PHB _LATD1
#define MOTOR1_PHC _LATD2
#define MOTOR1_PHD _LATD3
#define MOTOR2_PHA _LATD4
#define MOTOR2_PHB _LATD5
#define MOTOR2_PHC _LATD6
#define MOTOR2_PHD _LATD7

#define MOTOR1_PHA_DIR _TRISD0
#define MOTOR1_PHB_DIR _TRISD1
#define MOTOR1_PHC_DIR _TRISD2
#define MOTOR1_PHD_DIR _TRISD3
#define MOTOR2_PHA_DIR _TRISD4
#define MOTOR2_PHB_DIR _TRISD5
#define MOTOR2_PHC_DIR _TRISD6
#define MOTOR2_PHD_DIR _TRISD7

/*camera*/
#define CAM_RESET _LATC13
#define CAM_RESET_DIR _TRISC13

/* I2C */
#define SIO_D	_LATG3
#define SIO_D_DIR	_TRISG3

#define SIO_C	_LATG2
#define SIO_C_DIR	_TRISG2

/********************** INPUTS **************************/
#define INPUT_PIN 1

/*low battery signal active low when Vbatt<3.4V*/
#define BATT_LOW _RF1
#define BATT_LOW_DIR _TRISF1

/* selector on normal extension*/
#define SELECTOR0 _RG6
#define SELECTOR1 _RG7
#define SELECTOR2 _RG8
#define SELECTOR3 _RG9

#define SELECTOR0_DIR _TRISG6
#define SELECTOR1_DIR _TRISG7
#define SELECTOR2_DIR _TRISG8
#define SELECTOR3_DIR _TRISG9

/*IR TV receiver on normal extension*/
#define REMOTE _RF6
#define REMOTE_DIR _TRISF6

/*CAMERA*/
/*data higher 8 bits of port D*/
#define CAM_DATA PORTD;

#define CAM_y0 _RD8
#define CAM_y1 _RD9
#define CAM_y2 _RD10
#define CAM_y3 _RD11
#define CAM_y4 _RD12
#define CAM_y5 _RD13
#define CAM_y6 _RD14
#define CAM_y7 _RD15

#define CAM_y0_DIR _TRISD8
#define CAM_y1_DIR _TRISD9
#define CAM_y2_DIR _TRISD10
#define CAM_y3_DIR _TRISD11
#define CAM_y4_DIR _TRISD12
#define CAM_y5_DIR _TRISD13
#define CAM_y6_DIR _TRISD14
#define CAM_y7_DIR _TRISD15

/*clock interupt*/
#define CAM_PWDN _RC2
#define CAM_VSYNC _RC4
#define CAM_HREF _RC3
#define CAM_PCLK _RC14

#define CAM_PWDN_DIR _TRISC2
#define CAM_VSYNC_DIR _TRISC4
#define CAM_HREF_DIR _TRISC3
#define CAM_PCLK_DIR _TRISC14

/*********************** ASEMBLER SMALL FUNCTCION********************** */
#define NOP() {__asm__ volatile ("nop");}
#define CLRWDT() {__asm__ volatile ("clrwdt");}
#define SLEEP() {__asm__ volatile ("pwrsav #0");}
#define IDLE() {__asm__ volatile ("pwrsav #1");}
#define INTERRUPT_OFF() {__asm__ volatile ("disi	#10000");}
#define INTERRUPT_ON() {__asm__ volatile ("disi	#2");}
#define RESET() {__asm__ volatile ("reset");}	


#define STOP_TMR1 IEC0bits.T1IE = 0
#define STOP_TMR2 IEC0bits.T2IE = 0
#define STOP_TMR3 IEC0bits.T3IE = 0
#define STOP_TMR4 IEC1bits.T4IE = 0
#define STOP_TMR5 IEC1bits.T5IE = 0

#endif
