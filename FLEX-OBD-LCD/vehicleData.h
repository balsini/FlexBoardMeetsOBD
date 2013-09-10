/*
 * vehicleData.h
 *
 *  Created on: 10/set/2013
 *      Author: Alessio
 */

#ifndef VEHICLEDATA_H_
#define VEHICLEDATA_H_

#define VEHICLE_DATA_SIZE		3
#define VEHICLE_DATA_VERSION	0x00
#define VEHICLE_DATA_SPEED		0x01
#define VEHICLE_DATA_RPM		0x02

typedef struct vehicleData_ {
	char Elm327version[4];
	unsigned int speed;
	unsigned int RPM;
} vehicleData;

extern vehicleData vehicleDataBuffer;

#endif /* VEHICLEDATA_H_ */
