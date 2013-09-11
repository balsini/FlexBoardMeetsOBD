/*
 * vehicleData.h
 *
 *  Created on: 10/set/2013
 *      Author: Alessio
 */

#ifndef VEHICLEDATA_H_
#define VEHICLEDATA_H_

#define VEHICLE_DATA_SIZE		5
#define VEHICLE_DATA_VERSION	0x01
#define VEHICLE_DATA_SPEED		0x02
#define VEHICLE_DATA_RPM		0x04
#define VEHICLE_DATA_COOLANT_TEMP		0x08
#define VEHICLE_DATA_FUEL		0x16

typedef struct vehicleData_ {
	unsigned int ready;
	char Elm327version[4];
	unsigned int speed;
	unsigned int RPM;
	unsigned int coolantTemp;
	unsigned int fuelRemaining;
} vehicleData;

extern vehicleData vehicleDataBuffer;

#endif /* VEHICLEDATA_H_ */
