#include "misc.h"

#include <math.h>

void floatToBytes(float n, unsigned char *b)
{
	int i;
	mfloat x;

	x.i = n;
	for(i=0 ; i<4 ; i++) b[i] = x.b[i];
}


void doubleToBytes(double n, unsigned char *b)
{
	int i;
	mdouble x;

	x.i = n;
	for(i=0 ; i<8 ; i++) b[i] = x.b[i];
}


void longToBytes(long n, unsigned char *b)
{
	int i;
	mlong x;

	x.i = n;
	for(i=0 ; i<4 ; i++) b[i] = x.b[i];
}

void shortToBytes(short n, unsigned char *b)
{
	mshort x;

	x.i = n;
	b[1] = x.b[1];
	b[0] = x.b[0];
}


float bytesToFloat(unsigned char *b)
{
	int i;
	mfloat x;

	for(i=0 ; i<4 ; i++) x.b[i] = b[i];
	return(x.i);
}


double bytesToDouble(unsigned char *b)
{
	int i;
	mdouble x;

	for(i=0 ; i<8 ; i++) x.b[i] = b[i];
	return(x.i);
}


long bytesToLong(unsigned char *b)
{
	int i;
	mlong x;

	for(i=0 ; i<4 ; i++) x.b[i] = b[i];
	return(x.i);
}


short bytesToShort(unsigned char *b)
{
	mshort x;

	x.b[1] = b[1];
	x.b[0] = b[0];
	return(x.i);
}



void floatToBytes_inv(float n, unsigned char *b)
{
	int i;
	mfloat x;

	x.i = n;
	for(i=0 ; i<4 ; i++) b[3-i] = x.b[i];
}


void doubleToBytes_inv(double n, unsigned char *b)
{
	int i;
	mdouble x;

	x.i = n;
	for(i=0 ; i<8 ; i++) b[7-i] = x.b[i];
}

void longToBytes_inv(long n, unsigned char *b)
{
	int i;
	mlong x;

	x.i = n;
	for(i=0 ; i<4 ; i++) b[3-i] = x.b[i];
}


void shortToBytes_inv(short n, unsigned char *b)
{
	mshort x;

	x.i = n;
	b[0] = x.b[1];
	b[1] = x.b[0];
}


float bytesToFloat_inv(unsigned char *b)
{
	int i;
	mfloat x;

	for(i=0 ; i<4 ; i++) x.b[3-i] = b[i]; 
	return(x.i);
}

double bytesToDouble_inv(unsigned char *b)
{
	int i;
	mdouble x;

	for(i=0 ; i<8 ; i++) x.b[7-i] = b[i];
	return(x.i);
}


long bytesToLong_inv(unsigned char *b)
{
	int i;
	mlong x;

	for(i=0 ; i<4 ; i++) x.b[3-i] = b[i];
	return(x.i);
}


short bytesToShort_inv(unsigned char *b)
{
	mshort x;

	x.b[0] = b[1];
	x.b[1] = b[0];
	return(x.i);
}

#if 0
int safeSet(float *p, float k)
{
	if(finite(k)) { *p = k; return(0); }
	return(1);
}


int safeSetD(double *p, double k)
{
	if(finite(k)) { *p = k; return(0); }
	return(1);
}
#endif

