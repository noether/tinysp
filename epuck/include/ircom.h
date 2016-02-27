
#ifndef IRCOM_H
#define IRCOM_H

#include "e_ad_conv.h"

// constants that define behaviour of ircom module
#define IRCOM_WORDSIZE 8 // bits
#define IRCOM_RECEIVESPEED 100.0 // microseconds
#define IRCOM_MARK_SAMPLE_PER_PERIOD 3.0 
#define IRCOM_SPACE_SAMPLE_PER_PERIOD 6.0 
#define IRCOM_SAMPLING_WINDOW 32
#define IRCOM_MARK 0
#define IRCOM_SPACE 1
#define IRCOM_MARK_THRESHOLD 8 // min number of signal switch
#define IRCOM_SPACE_THRESHOLD 4 // min number of signal switch
#define IRCOM_NB_IR_SENSORS 8
#define IRCOM_DETECTION_THRESHOLD_AMPLITUDE 10 // min amplitude of signal
#define IRCOM_DETECTION_THRESHOLD_SWITCH 2 // min number of switch to initiate message

typedef char ircomWord[IRCOM_WORDSIZE + 4]; 

// structure that keeps all relevant information to run ircom module
// mainly which FSM is running, if any
#define IRCOM_FSM_IDLE 0
#define IRCOM_FSM_RECEIVE 1
#define IRCOM_FSM_SEND 2
typedef struct
{    
    int fsm;
} Ircom;

// structure that keeps track of all information related to receiveing
typedef struct
{
    // public :
    int receiving;
    int done;
    int error;
    ircomWord word;
    float distance;
    float direction;

    // private :
    int state;
    int currentBit;
    int receivingSensor;
} IrcomReceive;

// structure that keeps track of all information related to writing
#define IRCOM_SEND_OMNI 0
#define IRCOM_SEND_DIRECTIONNAL 1
typedef struct
{
    // public : 
    int done;
    ircomWord word;
    int type; // omni or directionnal    
    int sensor;

    // private : 
    int pulseState;
    int switchCounter;
    int switchCountMax;
    int signal;
    int currentBit;

    int markSwitchCount;
    int spaceSwitchCount;
    double markDuration;
    double spaceDuration;

    double durations[IRCOM_WORDSIZE+4];
    int switchCounts[IRCOM_WORDSIZE+4];
} IrcomSend;

extern volatile Ircom ircomData;
extern volatile IrcomReceive ircomReceiveData;
extern volatile IrcomSend ircomSendData;

//extern float sensorDir[NB_IR_SENSORS];

void ircomStart ();
void ircomStop (void);
void ircomRestart (void);
void ircomEnableProximity ();
void ircomDisableProximity ();


// make available to others read and write public functions
#include "ircomReceive.h"
#include "ircomSend.h"
#include "ircomTools.h"


#endif
