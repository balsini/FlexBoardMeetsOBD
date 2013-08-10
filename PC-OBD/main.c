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
	EE_bluetooth_init();
	EE_bluetooth_inquiry();
	EE_bluetooth_connect();

	ee_elm327_init();
	printf("Elm327 Version: %s", ee_elm327_get_version());

	EE_bluetooth_free();
	return 0;
}
