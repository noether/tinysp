
#ifndef IRCOM_TOOLS_H
#define IRCOM_TOOLS_H


float ircomEstimateDistance (int irPerceived);
float ircomEstimateDirection (int middleSensor);
void ircomInt2Bin (int n, ircomWord w);
int ircomBin2Int(volatile ircomWord w);

// IRCOM_TOOLS_H
#endif
