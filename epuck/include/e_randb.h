/********************************************************************************
 *
 *       Range and Bearing board of e-puck
 *       Version 1.0 January 2008
 *
 ********************************************************************************/


#ifndef _ERANDB
#define _ERANDB

#define RAB_ID 0x40

#define ON_BOARD 	0
#define ON_ROBOT 	1

#define FALSE 0
#define TRUE 1

#define WAITING 0
#define RECEIVING 1


typedef struct{
	unsigned char received;
	unsigned char alpha;
	unsigned int  data;
	unsigned int distance;
}randbReceptionStruct;

typedef struct {
	unsigned int data;
	float bearing;
	unsigned int range;
	unsigned int max_peak;
	unsigned char max_sensor;
} finalDataRegister;

/*volatile finalDataRegister erandbTmpData;*/
/*volatile finalDataRegister erandbFinalData;*/
/*volatile char* p;*/
/*volatile int erandbFinished;*/
/*volatile int erandbState;*/
/*volatile int erandbCounter;*/


extern int calcOnBoard;
/* Init the I2C and UART2 comunications */
void e_init_randb ( void );

/* State machine to get data from the UART
 * It is managed by the agenda */
void e_randb_get_uart2 ( void );

/* Get Data received from uart2 */
int e_randb_get_data_uart2 ( finalDataRegister* data);

/* READ FUNCTIONS */
/*get the last maximum sensor receiving*/
unsigned char e_randb_get_sensor ( void );

/*get last data received*/
unsigned int  e_randb_get_data( void );

/*get last distance */
unsigned int e_randb_get_range( void );

/*get last angle*/
double e_randb_get_bearing( void );

/*get if something received*/
unsigned char e_randb_get_if_received( void );

/*get last compleate reception*/
randbReceptionStruct e_randb_reception( void );

unsigned int e_randb_get_all_data ( unsigned int *peaks, unsigned int *data);
/*get all sensors values received*/
/*int e_randb_all_reception( unsigned int *peaks, unsigned int *data );*/
int e_randb_all_reception( unsigned int *range, float *bearing, unsigned int *data );



/* WRITE FUNCTIONS*/

/* Send the same data on all the channels*/
void e_randb_send_all_data( unsigned int data );

/* Store data in one channel */
void e_randb_store_data ( unsigned char channel , unsigned int data );

/* Send data Stored */
void e_randb_send_data ( void );

/* Change the range distance 
 * 0 -> maximum (1m. aprox)
 * 255 -> minimum  (1cm aprox)
 * Values depend on the light conditions of the environment
 * */

/* Set range of transmission */
void e_randb_set_range ( unsigned char distance);

/*get ambient light conditions*/
void e_randb_store_light_conditions ( void );
/* Chose who is going to make the calculations 
 *
 * ON_BOARD -> The board makes the calculations of the r&b
 * ON_ROBOT -> The robot makes the calculations of the r&b
 * */
void e_randb_set_calculation ( char value );

#endif
