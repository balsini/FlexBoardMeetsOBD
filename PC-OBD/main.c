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
	if (!EE_bluetooth_inquiry()) {
		printf("No device found\n");
		EE_bluetooth_connect_dev("00:0D:18:3A:73:9D");
		ee_elm327_init();
		printf("Elm327 Version: %s\n", ee_elm327_get_version());
		for (i=0; i<10; i++) {
			printf("Scan %d:\n",i);
			printf("\tRPM: %d\n", ee_elm327_get(ENGINE_RPM));
			printf("\tThrottle: %d\n", ee_elm327_get(THROTTLE_POSITION));
			printf("\tCoolant Temp: %d\n", ee_elm327_get(ENGINE_COOLANT_TEMP));
			printf("\tSpeed: %d\n", ee_elm327_get(VEHICLE_SPEED));
		}
	} else {
		if (EE_bluetooth_connect() == -1) {
			printf("Error during Bluetooth connection!\n");
		} else {
			ee_elm327_init();
			printf("Elm327 Version: %s\n", ee_elm327_get_version());
			for (i=0; i<10; i++) {
				printf("Scan %d:\n",i);
				printf("\tRPM: %d\n", ee_elm327_get(ENGINE_RPM));
				printf("\tThrottle: %d\n", ee_elm327_get(THROTTLE_POSITION));
				printf("\tCoolant Temp: %d\n", ee_elm327_get(ENGINE_COOLANT_TEMP));
				printf("\tSpeed: %d\n", ee_elm327_get(VEHICLE_SPEED));
			}
		}
	}
	EE_bluetooth_free();
	printf("Bye!\n");
	return 0;
}
