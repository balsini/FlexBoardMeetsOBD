/*
 * buttons.h
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "ee.h"
#include "ee_irq.h"
#include "LCD.h"
#include "constants.h"

/**
 * Checks the buttons status and
 * returns the signal associated.
 */

Signal getSignals();

/**
 * Initializes all the four buttons
 * and sets the buttons handler.
 */

void buttons_init();

/**
 * Returns a bitmask containing the
 * pushed buttons.
 */

char buttons_get();

#endif /* BUTTONS_H_ */
