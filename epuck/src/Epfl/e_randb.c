
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <e_epuck_ports.h>
#include <e_I2C_protocol.h>
#include <e_agenda.h>
#include <e_uart_char.h>
#include <btcom.h>

#include "e_randb.h"

int SensorAngle[] = {15,50,75,105,133,159,-165,-135,-105,-77,-50,-15};
float SensorAngleRads[] = {0.261799,0.872665,1.308997,1.832596,2.321288,2.775073,-2.879793,-2.356194,-1.832596,-1.343903,-0.872665,-0.261799};
float CosSensorAngle[] = {0.965926,0.642788,0.258819,-0.258819,-0.681998,-0.93358,-0.965926,-0.707107,-0.258819,0.224951,0.642788,0.965926};
float SinSensorAngle[] = {0.258819,0.766044,0.965926,0.965926,0.731354,0.358368,-0.258819,-0.707107,-0.965926,-0.97437,-0.766044,-0.258819};

int calcOnBoard;

volatile finalDataRegister erandbTmpData;
volatile finalDataRegister erandbFinalData;
volatile char* p = (&erandbTmpData);
volatile int erandbFinished;
volatile int erandbState;
volatile int erandbCounter;

void e_init_randb ( void )
{
	/* Init I2C */
	e_i2cp_init();
	e_i2cp_enable();

	/* Init UART2 */
	e_init_uart2();

	/* Clean UART buffer */
	char msg;
	while(e_getchar_uart2(&msg));

	/* Calculations are made on the BOARD*/
	calcOnBoard = TRUE;

	/**p = (&erandbTmpData);*/
	erandbFinished = FALSE;
	erandbState = WAITING;
	erandbCounter = 0;

	e_activate_agenda(e_randb_get_uart2, 2);
}

void e_randb_get_uart2 ( void )
{	
	char tmp[150];
	/* If char received */
	/*char msg;*/
	/*if (e_getchar_uart2(&msg))*/
	if (e_getchar_uart2(p))
	{
		/*sprintf(tmp,"DATA: %d Counter %d\n",*p,erandbCounter);*/
		/*sprintf(tmp,"DATA: %d Counter %d\n",msg,erandbCounter);*/
		/*sprintf(tmp,"DATA %d\n",erandbFinished);*/
		/*btcomSendString(tmp);*/

		erandbCounter++;
		p++;
		
		switch(erandbState)
		{
			case WAITING:
				erandbState = RECEIVING;
				erandbCounter = 1;
				break;
			case RECEIVING:
				if ( erandbCounter == 12)
				{
					/*sprintf(tmp,"DATA: %u Bearing: %2f Range: %u Max_Peak: %u, Max_Sensors: %u\n",erandbTmpData.data, erandbTmpData.bearing,erandbTmpData.range,erandbTmpData.max_peak,erandbTmpData.max_sensor);*/
					/*btcomSendString(tmp);*/
					
					erandbFinalData = erandbTmpData;
					erandbFinished = TRUE;
					erandbCounter = 0;
					erandbState = WAITING;
					
					/*sprintf(tmp,"DATA: %u \n",erandbFinalData.data);*/
					/*btcomSendString(tmp);*/
				}
				break;
		}
	}
	/* If no char received during 10 agendas cycles (1ms) */
	else
	{
		/*sprintf(tmp,"----------------- RESET --------------------%d\n",erandbFinished);*/
		/*btcomSendString(tmp);*/
		/*long int i;*/
		/*for ( i = 0 ; i < 100 ; i++)*/
		/*{*/
		/*asm("nop");*/
		/*}*/
		p = &(erandbTmpData);
		erandbFinished = erandbFinished;
		erandbState = WAITING;
		erandbCounter = 0;
	}
}

int e_randb_get_data_uart2 ( finalDataRegister* data)
{
	char tmp[100];
	/*sprintf(tmp,"READ %d\n",erandbFinished);*/
	/*btcomSendString(tmp);*/
	
	if (erandbFinished == TRUE)
	{
		/*sprintf(tmp,"TRUE\n");*/
		/*btcomSendString(tmp);*/
		
		*data = erandbFinalData;
		erandbFinished = FALSE;
		return TRUE;
	}
	else{
		/*sprintf(tmp,"FALSE\n");*/
		/*btcomSendString(tmp);*/
		return FALSE;
	}
}



unsigned char e_randb_get_if_received( void ){	
	return e_i2cp_read(RAB_ID,0);
}

unsigned char  e_randb_get_sensor( void ){
	return  e_i2cp_read(RAB_ID,9);
	
}

unsigned int  e_randb_get_peak( void ){
		unsigned char aux1;
		unsigned char aux2;
		aux1 = e_i2cp_read(RAB_ID,7);
		aux2 = e_i2cp_read(RAB_ID,8);
		return (((unsigned int) aux1) << 8) + aux2;
}
unsigned int e_randb_get_data( void )
{
	unsigned char aux1;
	unsigned char aux2;
	aux1 = e_i2cp_read(RAB_ID,1);
	aux2 = e_i2cp_read(RAB_ID,2);
	unsigned int data = (((unsigned int) aux1) << 8) + aux2;
	return data;
}

unsigned int e_randb_get_range( void ){	

	unsigned char aux1;
	unsigned char aux2;
	aux1 = e_i2cp_read(RAB_ID,5);
	aux2 = e_i2cp_read(RAB_ID,6);
	unsigned int data = (((unsigned int) aux1) << 8) + aux2;
	return data;
}

double e_randb_get_bearing ( void )
{
	unsigned char aux1;
	unsigned char aux2;
	aux1 = e_i2cp_read(RAB_ID,3);
	aux2 = e_i2cp_read(RAB_ID,4);
	int angle = (((unsigned int) aux1) << 8) + aux2;
	return ( ((double) angle) * 0.0001);
}

randbReceptionStruct e_randb_reception( void )
{
	randbReceptionStruct value;
	/*value.received = 0;*/
	/*if(e_randb_get_if_received() != 0){*/
	/*value.received = 1;*/
	/*value.alpha = e_randb_get_sensor();*/
	/*value.data = e_randb_get_data();*/
	/**//**//*value.distance = e_randb_get_distance();*/
	/*}*/
	return value;
}

unsigned int e_randb_get_all_data ( unsigned int *peaks, unsigned int *data)
{

	if(e_i2cp_read(RAB_ID,20) != 0){
		int i;
		for ( i = 0 ; i < 12 ; i ++){
			unsigned char aux1;
			unsigned char aux2;
			aux1 = e_i2cp_read(RAB_ID,21+(2*i));
			aux2 = e_i2cp_read(RAB_ID,21+((2*i)+1));
			peaks[i] = (((unsigned int) aux1) << 8) + aux2;
		}
		
		unsigned char aux1;
		unsigned char aux2;
		aux1 = e_i2cp_read(RAB_ID,45);
		aux2 = e_i2cp_read(RAB_ID,46);
		*data = (((unsigned int) aux1) << 8) + aux2;

		return 1;
	}
	else
	{
		return 0;
	}
}

int e_randb_all_reception( unsigned int *range, float *bearing, unsigned int *data )
{
	unsigned int peaks[12];
	if(e_i2cp_read(RAB_ID,20) != 0){
		int i;
		for ( i = 0 ; i < 12 ; i ++){
			unsigned char aux1;
			unsigned char aux2;
			aux1 = e_i2cp_read(RAB_ID,21+(2*i));
			aux2 = e_i2cp_read(RAB_ID,21+((2*i)+1));
			peaks[i] = (((unsigned int) aux1) << 8) + aux2;
		}

		/*char tmp2[100];*/
		/*sprintf(tmp2,"%u %u %u %u %u %u %u %u %u %u %u %u",peaks[0],peaks[1],peaks[2],peaks[3],peaks[4],peaks[5],peaks[6],peaks[7],peaks[8],peaks[9],peaks[10],*/
		/*peaks[11]);*/
		/*btcomSendString(tmp2);*/
		/*btcomSendString("\n");*/

		float x=0;
		float y=0;

		unsigned int max_peak1=0;
		unsigned int max_peak2=0;
		char max_sensor1=0;
		char max_sensor2=0;
		int num_sensors;
		for (num_sensors = 0 ; num_sensors < 12 ; num_sensors++)
		{
			unsigned int distance = peaks[num_sensors];
			if ( distance != 0)
			{
				x += distance * CosSensorAngle[num_sensors];
				y += distance * SinSensorAngle[num_sensors];

				if ( distance > max_peak1 )
				{
					max_peak2 = max_peak1;
					max_sensor2 = max_sensor1;
					max_peak1 = distance;
					max_sensor1 = num_sensors;
				}
				else if (distance > max_peak2 )
				{
					max_peak2 = distance;
					max_sensor2 = num_sensors;
				}
			}
		}

		/*char tmp2[100];*/
		/*sprintf(tmp2,"%u %d %u %d ",max_sensor1, max_peak1, max_sensor2, max_peak2);*/
		/*btcomSendString(tmp2);*/
		/*btcomSendString("\n");*/
		
		/*Calc Angle */
		if (x == 0.0 && y == 0.0 ) return 0;
		float angle = atan2(y,x);
		/* Calc Distance */
		float v1 = (float) max_peak1 * (float) max_peak1;
		v1*=v1;
		float v2 = (float) max_peak2 * (float) max_peak2;
		v2*=v2;

		float cos1 = cos ( angle - SensorAngleRads[max_sensor1] ); 
		cos1 *= cos1;
		float cos2 = cos ( angle - SensorAngleRads[max_sensor2] ); 
		cos2 *= cos2;
		v1 /= cos1;
		v2 /= cos2;
		*range = (unsigned int ) sqrt(sqrt(v1+v2));
		/* Calc Data */
		unsigned char aux1;
		unsigned char aux2;
		aux1 = e_i2cp_read(RAB_ID,45);
		aux2 = e_i2cp_read(RAB_ID,46);
		*data = (((unsigned int) aux1) << 8) + aux2;
		*bearing = angle;
		return 1;
	}
	return 0;
}

void e_randb_send_all_data( unsigned int data ){
	e_i2cp_write(RAB_ID,13,(data>>8) & 0xFF);
	e_i2cp_write(RAB_ID,14,(data & 0xFF));
}

void e_randb_store_data ( unsigned char channel , unsigned int data ){
	e_i2cp_write(RAB_ID,channel,data);

	e_i2cp_write(RAB_ID,13,(data>>8) & 0xFF);
	e_i2cp_write(RAB_ID,channel,(data & 0xFF));
}

void e_randb_send_data ( void ){
	e_i2cp_write(RAB_ID,15,0);
}


void e_randb_set_range ( unsigned char distance){
	e_i2cp_write(RAB_ID,12,distance);
}

void e_randb_store_light_conditions ( void ){
	e_i2cp_write(RAB_ID,16,0);
}

void e_randb_set_calculation ( char value ) {
	calcOnBoard = value;
	e_i2cp_write(RAB_ID,17,value);
		
}

