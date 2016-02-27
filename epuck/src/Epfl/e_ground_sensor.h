/********************************************************************************
 *
 *       Ground sensor  of e-puck
 *       Version 1.0 January 2008
 *
 ********************************************************************************/

#include <e_I2C_protocol.h>

/* Init the I2C comunication */
void e_init_ground_sensors ( void );

/* *
 * Get the value:
 * 	value[0]: Right
 * 	value[1]: Center 
 * 	value[2]: Left
 * 	*/
void e_get_ground_sensors( unsigned int value[3]);
