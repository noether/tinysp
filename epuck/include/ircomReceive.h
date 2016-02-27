
#ifndef IRCOM_RECEIVE_H
#define IRCOM_RECEIVE_H

// public
void ircomReceive();
int ircomReceiveDone();
inline int ircomIsReceiving ();

// private
void ircomReceiveMain();
void ircomReceiveListen();
void ircomReceiveWord();
int ircomReceiveGetMaxSensor();
int ircomReceiveDemodulate();
int ircomReceiveCheckCRC();


// IRCOM_RECEIVE_H
#endif
