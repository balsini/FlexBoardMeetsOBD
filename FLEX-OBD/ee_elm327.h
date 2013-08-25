/*
 * ee_elm327.h
 *
 *  Created on: 08/ago/2013
 *      Author: Alessio
 */

#ifndef EE_ELM327_H_
#define EE_ELM327_H_

// Mode, PID, Return byte num
typedef struct MPR_t_ {
	char mode[3];
	char PID[3];
	char return_byte_num;
} MPR_t;

typedef enum MPR_index_t_ {
	ENGINE_COOLANT_TEMP = 0,
	ENGINE_RPM,
	VEHICLE_SPEED,
	THROTTLE_POSITION
} MPR_index_t;

/*
 * Initializes the module.
 */

void ee_elm327_init();

/*
 * Enables (val = 1) or disables (val = 0)
 * device's echo.
 */

int ee_elm327_set_echo(char val);

/*
 * Reboots the Elm327 module.
 */

int ee_elm327_reboot();

/*
 * Returns a string containing the version
 * of the connected Elm device
 */

char * ee_elm327_get_version();

/*
 * Returns the value of the vehicle's
 * chosen data
 */

int ee_elm327_get(MPR_index_t identifier);

#endif /* EE_ELM327_H_ */
