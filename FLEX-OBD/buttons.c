/*
 * buttons.c
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#include "buttons.h"

char buttons_pressed;

void buttons_handler()
{
	if (EE_button_get_S1())
		buttons_pressed |= 1;
	if (EE_button_get_S2())
		buttons_pressed |= 2;
	if (EE_button_get_S3())
		buttons_pressed |= 4;
	if (EE_button_get_S4())
		buttons_pressed |= 8;
}

char buttons_get()
{
	char b = buttons_pressed;
	buttons_pressed ^= buttons_pressed;
	return b;
}

void buttons_init()
{
	buttons_pressed = 0;
	EE_buttons_init(buttons_handler, 0xF);
}
