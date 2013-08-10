/*
 * main.c
 *
 *  Created on: Aug 10, 2013
 *      Author: alessio
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "bluetooth.h"
#include "ee_elm327.h"

int main(int argc, char ** argv)
{
	int i;

	EE_bluetooth_init();
	EE_bluetooth_inquiry();
	EE_bluetooth_connect();

	ee_elm327_init();
	printf("Elm327 Version: %s\n", ee_elm327_get_version());
	for (i=0; i<10; i++) {
		printf("Throttle: %d\n", ee_elm327_get(THROTTLE_POSITION));
		printf("RPM: %d\n", ee_elm327_get(ENGINE_COOLANT_TEMP));
		printf("Coolant Temp: %d\n", ee_elm327_get(ENGINE_RPM));
		printf("Speed: %d\n", ee_elm327_get(VEHICLE_SPEED));
	}
	EE_bluetooth_free();
	return 0;
}
