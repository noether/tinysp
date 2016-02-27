
#ifndef IRCOM_SEND_H
#define IRCOM_SEND_H

// user interface
void ircomSend (ircomWord w);
void ircomDirectionnalSend (ircomWord w, int sensor);
int ircomSendDone ();
inline int ircomIsSending ();

// module related
void ircomSendCalcSending(ircomWord w);
void ircomSendMain();
void ircomSendSync();
void ircomSendOut();
void ircomSendNextBit();

// IRCOM_SEND_H
#endif
