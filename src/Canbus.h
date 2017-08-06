/**
 * CAN BUS
 *
 * Copyright (c) 2010 Sukkin Pang All rights reserved.
 */

#ifndef canbus__h
#define canbus__h

#include "speeds.h"

#define ENGINE_COOLANT_TEMP 0x05
#define ENGINE_RPM          0x0C
#define VEHICLE_SPEED       0x0D
#define MAF_SENSOR          0x10
#define O2_VOLTAGE          0x14
#define THROTTLE			0x11

#define PID_REQUEST         0x7DF
#define PID_REPLY			0x7E8

class CanbusClass
{
  public:

	CanbusClass();
    char init(unsigned char, unsigned char);
	char message_tx(void);
	char message_rx(unsigned char *buffer);
	char ecu_req(unsigned char pid,  char *buffer);
private:
	
};
extern CanbusClass Canbus;
//extern tCAN message;

#endif
