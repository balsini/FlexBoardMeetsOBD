/*
 * vehicleData.h
 *
 *  Created on: 10/set/2013
 *      Author: Alessio
 */

#ifndef VEHICLEDATA_H_
#define VEHICLEDATA_H_

/**
 * The number of data that can be requested
 * to the Elm327.
 */

#define VEHICLE_DATA_SIZE		5

/**
 * The version index in ready bitmask.
 */

#define VEHICLE_DATA_VERSION	0x01

/**
 * The speed index in ready bitmask.
 */

#define VEHICLE_DATA_SPEED		0x02

/**
 * The RPM index in ready bitmask.
 */

#define VEHICLE_DATA_RPM		0x04

/**
 * The coolant temperature index in
 * ready bitmask.
 */

#define VEHICLE_DATA_COOLANT_TEMP		0x08

/**
 * The fuel level index in ready bitmask.
 */

#define VEHICLE_DATA_FUEL		0x16


/**
 * The struct of vehicle data.
 */

typedef struct vehicleData_ {
	unsigned int ready;
	unsigned int speed;
	unsigned int RPM;
	unsigned int coolantTemp;
	unsigned int fuelRemaining;
} vehicleData;

/**
 * The global buffer containing vehicle data.
 */

extern vehicleData vehicleDataBuffer;

#endif /* VEHICLEDATA_H_ */
