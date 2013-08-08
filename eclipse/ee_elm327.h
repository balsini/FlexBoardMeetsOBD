/*
 * ee_elm327.h
 *
 *  Created on: 08/ago/2013
 *      Author: Alessio
 */

#ifndef EE_ELM327_H_
#define EE_ELM327_H_

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

#endif /* EE_ELM327_H_ */
