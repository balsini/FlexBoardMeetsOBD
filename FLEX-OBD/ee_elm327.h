/*
 * ee_elm327.h
 *
 *  Created on: 08/ago/2013
 *      Author: Alessio
 */

#ifndef EE_ELM327_H_
#define EE_ELM327_H_

/**
 * The row structure needed in OBDII protocol:
 *
 * Mode: the OBDII mode identifier.
 *
 * PID: the OBDII PID identifier.
 *
 * Return byte num: the size (in bytes) of the response.
 */

typedef struct MPR_t_ {
	char mode[3];
	char PID[3];
	char return_byte_num;
} MPR_t;

/**
 * The MPR_t array identifier, for making it easier
 * (more user friendly) to request vehicle data.
 */

typedef enum MPR_index_t_ {
	ENGINE_COOLANT_TEMP = 0,
	ENGINE_RPM,
	VEHICLE_SPEED,
	THROTTLE_POSITION,
	FUEL_REMAINING
} MPR_index_t;

/**
 * The Elm327 version.
 */

extern char version[4];

/**
 * Initializes the module.
 */

void ee_elm327_init();

/**
 * Enables or disables Elm327 echo.
 * @param value 1: enables, 0: disables.
 * @return 1 if everything worked fine.
 */

int ee_elm327_set_echo(char val);

/**
 * Reboots the Elm327 module.
 * @return 1 if everything worked fine.
 */

int ee_elm327_reboot();

/**
 * Returns the version of the connected
 * Elm327 device.
 * @return the string containing the Elm327
 * version
 */

char * ee_elm327_get_version();

/**
 * Returns the value of the vehicle's
 * chosen data.
 * @param identifier The data requested.
 * @return The Elm327 response, converted
 * from ASCII to integer.
 */

int ee_elm327_get(MPR_index_t identifier);

#endif /* EE_ELM327_H_ */
