#ifndef LCD_H_
#define LCD_H_

#include "ee.h"
#include "ee_irq.h"

void LCD_init();

/*
 * Clears the lcd row line and writes the string
 * str in that row.
 */

void LCD_write(char line, char * str);

/*
 * Appends a new row to the lcd, shifting the previous
 * above.
 */

void LCD_append_row(char * str);

/*
 * Appends the string str to the last row.
 */

void LCD_append(char * str);

#endif /* LCD_H_ */
