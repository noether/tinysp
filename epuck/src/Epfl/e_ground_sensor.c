
#include <e_ground_sensor.h>

void e_init_ground_sensors ( void )
{
	e_i2cp_init();
	e_i2cp_enable();
}


void e_get_ground_sensors( unsigned int value[3])
{

	unsigned char buffer[6];

	int i;

	for (i=0; i<6; i++) buffer[i] = (unsigned char ) e_i2cp_read(0xC0,i);

	value[0] = (unsigned int) buffer[1] + ((unsigned int)buffer[0] << 8);
	value[1] = (unsigned int) buffer[3] + ((unsigned int)buffer[2] << 8);
	value[2] = (unsigned int) buffer[5] + ((unsigned int)buffer[4] << 8);
}
