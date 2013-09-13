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

void vehicleScan()
{
	printf("AAA\n");
	//printf("\tThrottle: %d\n", ee_elm327_get(THROTTLE_POSITION));
	printf("\tSpeed: %d\tRPM: %d\tCoolant Temp: %d\n", ee_elm327_get(VEHICLE_SPEED),ee_elm327_get(ENGINE_RPM)/4,ee_elm327_get(ENGINE_COOLANT_TEMP)-40);
	/*printf("\tRPM: %d\n", ee_elm327_get(ENGINE_RPM));*/
}

int main(int argc, char ** argv)
{
	EE_bluetooth_init();
	if (!EE_bluetooth_inquiry()) {
		printf("No device found\n");
		EE_bluetooth_connect_dev("00:0D:18:3A:73:9D");
		ee_elm327_init();
		printf("Elm327 Version: %s\n", ee_elm327_get_version());
		for (;;) {
			vehicleScan();
		}
	} else {
		if (EE_bluetooth_connect() == -1) {
			printf("Error during Bluetooth connection!\n");
		} else {
			ee_elm327_init();
			printf("Elm327 Version: %s\n", ee_elm327_get_version());
			for (;;) {
				vehicleScan();
			}
		}
	}
	EE_bluetooth_free();
	printf("Bye!\n");
	return 0;
}
