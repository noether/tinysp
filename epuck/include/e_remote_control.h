/********************************************************************
* 			control IR receiver module								*
*			september 2005 : first version							*
*			Valentin Longchamp										*
*																	*
********************************************************************/

/*! \file
 * \ingroup motor_LED
 * \brief Manage the IR receiver module (timer2)
 *
 * This module manage the IR receiver with the agenda solution (timer2).
 *
 * A little exemple to manage the IR remote (the body LED change his state when 
 * you press a button of the IR controller).
 * \code
 * #include <p30f6014A.h>
 * #include <motor_led/e_epuck_ports.h>
 * #include <motor_led/e_init_port.h>
 * #include <motor_led/advance_one_timer/e_remote_control.h>
 * #include <motor_led/advance_one_timer/e_agenda.h>
 * 
 * int main(void)
 * {
 * 	int ir_check;
 * 	int previous_check = 0;
 * 	e_init_port();
 * 	e_init_remote_control();
 * 	e_start_agendas_processing();
 * 	while(1)
 * 	{
 * 		ir_check = e_get_check();
 * 		if(ir_check != previous_check)
 * 			BODY_LED = BODY_LED^1;
 * 		previous_check = ir_check;
 * 	}
 * }
 * \endcode
 * \sa e_agenda.h
 * \author Jonathan Besuchet
 */

#ifndef _IR_REMOTE_CONTROLE
#define _IR_REMOTE_CONTROLE

/* defines for the keys on the remote controler
 * the numbers 0 to 9 are not defined since they are the same */
#define BOTTOMR		10 	// -/-- key
#define BOTTOMl		11 	// p<p key
#define	STANDBY		12 
#define MUTE		13
#define VOL_UP		16
#define VOL_DOWN	17
#define CHAN_UP		32
#define CHAN_DOWN	33
#define I_II		35
#define OUT_AUX_1	56



/* functions */
void e_init_remote_control(void);
void e_read_remote_control(void);

unsigned char e_get_check(void);
unsigned char e_get_address(void);
unsigned char e_get_data(void);

#endif
