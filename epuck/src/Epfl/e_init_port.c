/*************************************************************************
* 			Initialization of port of e-puck		 *
*			Version 1.0 november 2005       		 *
*			Michael Bonani, Francesco Mondada, Davis Dadie	 *
*									 *
*************************************************************************/



#include "e_epuck_ports.h"

void e_init_port(void)
{

/********************** OUTPUTS ***************************/
	/*LEDS*/
	LED0 = 0;
	LED1 = 0;
	LED2 = 0;
	LED3 = 0;
	LED4 = 0;
	LED5 = 0;
	LED6 = 0;
	LED7 = 0;
	LED0_DIR = OUTPUT_PIN;
	LED1_DIR = OUTPUT_PIN;
	LED2_DIR = OUTPUT_PIN;
	LED3_DIR = OUTPUT_PIN;
	LED4_DIR = OUTPUT_PIN;
	LED5_DIR = OUTPUT_PIN;
	LED6_DIR = OUTPUT_PIN;
	LED7_DIR = OUTPUT_PIN;
	
	FRONT_LED = 0;
	FRONT_LED_DIR = OUTPUT_PIN;

	BODY_LED = 0;
	BODY_LED_DIR = OUTPUT_PIN;

	/*IR*/
	PULSE_IR0 = 0;
	PULSE_IR1 = 0;
	PULSE_IR2 = 0;
	PULSE_IR3 = 0;
	PULSE_IR0_DIR = OUTPUT_PIN;
	PULSE_IR1_DIR = OUTPUT_PIN;
	PULSE_IR2_DIR = OUTPUT_PIN;
	PULSE_IR3_DIR = OUTPUT_PIN;

	/*basic audio*/
	AUDIO_ON = 0; /*turn of speaker and codec*/
	AUDIO_ON_DIR = OUTPUT_PIN;
	
	/*motors*/
	MOTOR1_PHA = 0;
	MOTOR1_PHB = 0;
	MOTOR1_PHC = 0;
	MOTOR1_PHD = 0;
	MOTOR2_PHA = 0;
	MOTOR2_PHB = 0;
	MOTOR2_PHC = 0;
	MOTOR2_PHD = 0;
	MOTOR1_PHA_DIR = OUTPUT_PIN;
	MOTOR1_PHB_DIR = OUTPUT_PIN;
	MOTOR1_PHC_DIR = OUTPUT_PIN;
	MOTOR1_PHD_DIR = OUTPUT_PIN;
	MOTOR2_PHA_DIR = OUTPUT_PIN;
	MOTOR2_PHB_DIR = OUTPUT_PIN;
	MOTOR2_PHC_DIR = OUTPUT_PIN;
	MOTOR2_PHD_DIR = OUTPUT_PIN;
	
	/*camera*/
	CAM_RESET=0;
	CAM_RESET_DIR = OUTPUT_PIN;
	
	/*I2C*/
	SIO_C=0;
	SIO_D=0;
	
	SIO_C_DIR= OUTPUT_PIN;
	SIO_D_DIR= OUTPUT_PIN;
	
/********************** INPUTS **************************/
	
	/*low battery signal active low when Vbatt<3.4V*/
	BATT_LOW_DIR = INPUT_PIN;
	
	/*IR TV receiver on normal extension*/
	REMOTE_DIR = INPUT_PIN;
	
	/* selector*/
	SELECTOR0_DIR = INPUT_PIN;
	SELECTOR1_DIR = INPUT_PIN;
	SELECTOR2_DIR = INPUT_PIN;
	SELECTOR3_DIR = INPUT_PIN;
	BATT_LOW_DIR = INPUT_PIN;
	
	/*camera*/
	CAM_y0_DIR = INPUT_PIN;
	CAM_y1_DIR = INPUT_PIN;
	CAM_y2_DIR = INPUT_PIN;
	CAM_y3_DIR = INPUT_PIN;
	CAM_y4_DIR = INPUT_PIN;
	CAM_y5_DIR = INPUT_PIN;
	CAM_y6_DIR = INPUT_PIN;
	CAM_y7_DIR = INPUT_PIN;	
}
