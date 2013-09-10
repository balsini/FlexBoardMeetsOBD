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

/*
 * Initialize button's handler
 */
Signal getSignals();
void buttons_init();
char buttons_get();

#endif /* BUTTONS_H_ */
