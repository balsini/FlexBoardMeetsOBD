#ifndef LCD_H_
#define LCD_H_

#include "ee.h"
#include "ee_irq.h"

void LCD_init();


/*
 * Writes the character c to the defined position
 * (x,y)
 */

void LCD_writeC(int x, int y, char c);

/*
 * Appends a new row to the lcd, shifting the previous
 * above.
 */

void LCD_append_row(char * str);

/*
 * Appends the string str to the last row.
 */

void LCD_append(char * str);
void LCD_appendC(char);

#endif /* LCD_H_ */
