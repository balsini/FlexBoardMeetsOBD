#include "LCD.h"

#define LCD_WIDTH 16

char LCD_ROW_0[LCD_WIDTH];
char LCD_ROW_1[LCD_WIDTH];
char append_pos;	// Traces the length of the written string
					// so that it will be possible to concatenate
					// other characters to it.

void LCD_update()
{
	int i;
	EE_lcd_goto(0, 0);
	for (i=0; i<LCD_WIDTH; i++)
		EE_lcd_putc(LCD_ROW_0[i]);
	EE_lcd_goto(0, 1);
	for (i=0; i<LCD_WIDTH; i++)
		EE_lcd_putc(LCD_ROW_1[i]);
}

void LCD_init()
{
	unsigned int i;
	EE_lcd_init();
	EE_lcd_clear();
	for (i=0; i<LCD_WIDTH; i++)
		LCD_ROW_0[i] = LCD_ROW_1[i] = ' ';
	LCD_append_row("    WELCOME!");
	LCD_append_row("  Flex2OBD 0.1");
}

void LCD_write(char line, char * str)
{
	unsigned int i;
	EE_lcd_goto(0, line);
	for (i=0; i<LCD_WIDTH; i++)
		EE_lcd_putc(' ');
	EE_lcd_goto(0, line);
	while (*str != '\0') {
		EE_lcd_putc((unsigned char)*str);
		str++;
	}
}

void LCD_append(char * str)
{
	unsigned int i;
	for (i=append_pos; *str != '\0' && i<LCD_WIDTH; i++) {
		LCD_ROW_1[i] = (unsigned char)*str;
		str++;
	}
	append_pos = i;
	for (; i<LCD_WIDTH; i++)
		LCD_ROW_1[i] = ' ';
	LCD_update();
}

void LCD_append_row(char * str)
{
	unsigned int i;
	for (i=0; i<LCD_WIDTH; i++)
		LCD_ROW_0[i] = LCD_ROW_1[i];
	for (i=0; *str != '\0' && i<LCD_WIDTH; i++) {
		LCD_ROW_1[i] = (unsigned char)*str;
		str++;
	}
	append_pos = i;
	for (; i<LCD_WIDTH; i++)
		LCD_ROW_1[i] = ' ';
	LCD_update();
}


