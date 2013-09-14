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

/**
 * Initializes and clears the LCD.
 */

void LCD_init();

/**
 * Writes a string to selected row.
 * @param row: the chosen row (0 or 1).
 * @param str: the string to be printed.
 */

void LCD_writeR(int row, char * str);

/**
 * Writes a character to the defined position
 * @param x the x axis.
 * @param y the y axis.
 * @param c the character to be printed.
 */

void LCD_writeC(int x, int y, char c);

/**
 * Appends a new row to the lcd, shifting the previous
 * above.
 */

void LCD_appendR(char * str);

/**
 * Appends the string to the last written row.
 * @param str the string to be printed.
 */

void LCD_appendS(char * str);

/**
 * Appends the char c to the last written row.
 * @param c the character to be printed.
 */

void LCD_appendC(char c);

#endif /* LCD_H_ */
