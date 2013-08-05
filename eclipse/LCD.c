#include "LCD.h"

#define LCD_WIDTH 16

char LCD_ROW_0[LCD_WIDTH];
char LCD_ROW_1[LCD_WIDTH];
char append_pos[2];	// Traces the length of the written string
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

	GetResource(LCD_MUTEX);

	EE_lcd_init();
	EE_lcd_clear();
	for (i=0; i<LCD_WIDTH; i++)
		LCD_ROW_0[i] = LCD_ROW_1[i] = ' ';

	ReleaseResource(LCD_MUTEX);
}

void LCD_writeC(int x, int y, char c)
{
	GetResource(LCD_MUTEX);

	append_pos[0] = x + 1;
	append_pos[1] = y + 1;
	if (y == 0) {
		LCD_ROW_0[x] = c;
	} else {
		LCD_ROW_1[x] = c;
	}
	LCD_update();

	ReleaseResource(LCD_MUTEX);
}


void LCD_writeR(int row, char * str)
{
	int i;

	GetResource(LCD_MUTEX);

	append_pos[1] = row;
	if (row == 0) {
		for (i=0; *str != '\0' && i<LCD_WIDTH; i++) {
			LCD_ROW_0[i] = *str;
			str++;
		}
		append_pos[0] = i;
		for (; i<LCD_WIDTH; i++)
			LCD_ROW_0[i] = ' ';
	} else {
		for (i=0; *str != '\0' && i<LCD_WIDTH; i++) {
			LCD_ROW_1[i] = *str;
			str++;
		}
		append_pos[0] = i;
		for (; i<LCD_WIDTH; i++)
			LCD_ROW_1[i] = ' ';
	}
	LCD_update();

	ReleaseResource(LCD_MUTEX);
}

inline void LCD_append(char * str)
{
	unsigned int i;
	for (i=append_pos[0]; *str != '\0' && i<LCD_WIDTH; i++) {
		if (append_pos[1])
			LCD_ROW_1[i] = (unsigned char)*str;
		else
			LCD_ROW_0[i] = (unsigned char)*str;
		str++;
	}
	append_pos[0] = i;
	for (; i<LCD_WIDTH; i++) {
		if (append_pos[1])
			LCD_ROW_1[i] = ' ';
		else
			LCD_ROW_0[i] = ' ';
	}
	LCD_update();
}

void LCD_appendS(char * str)
{
	GetResource(LCD_MUTEX);

	LCD_append(str);

	ReleaseResource(LCD_MUTEX);
}

void LCD_appendC(char c)
{
	char str[2];

	GetResource(LCD_MUTEX);

	str[0] = c;
	str[1] = '\0';
	LCD_append(str);

	ReleaseResource(LCD_MUTEX);
}

void LCD_appendR(char * str)
{
	unsigned int i;

	GetResource(LCD_MUTEX);

	append_pos[1] = 1;
	for (i=0; i<LCD_WIDTH; i++)
		LCD_ROW_0[i] = LCD_ROW_1[i];
	for (i=0; *str != '\0' && i<LCD_WIDTH; i++) {
		LCD_ROW_1[i] = (unsigned char)*str;
		str++;
	}
	append_pos[0] = i;
	for (; i<LCD_WIDTH; i++)
		LCD_ROW_1[i] = ' ';
	LCD_update();

	ReleaseResource(LCD_MUTEX);
}
