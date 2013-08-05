/*
 * LCD.h
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#ifndef LCD_H_
#define LCD_H_

#include "ee.h"
#include "ee_irq.h"

void LCD_init();

/*
 * Writes the string str to selected row
 */

void LCD_writeR(int row, char * str);

/*
 * Writes the character c to the defined position
 * (x,y)
 */

void LCD_writeC(int x, int y, char c);

/*
 * Appends a new row to the lcd, shifting the previous
 * above.
 */

void LCD_appendR(char * str);

/*
 * Appends the string str to the last written row.
 */

void LCD_appendS(char * str);

/*
 * Appends the char c to the last written row.
 */

void LCD_appendC(char c);

#endif /* LCD_H_ */
