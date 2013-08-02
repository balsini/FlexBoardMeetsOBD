#include "ee.h"
#include "ee_irq.h"
#include "ee_bluetooth.h"

#define LCD_WIDTH 16

// Primary (XT, HS, EC) Oscillator with PLL
_FOSCSEL(FNOSC_PRIPLL);
// OSC2 Pin Function: OSC2 is Clock Output - Primary Oscillator Mode: XT Crystanl
_FOSC(OSCIOFNC_ON & POSCMD_XT);
// Watchdog Timer Enabled/disabled by user software
_FWDT(FWDTEN_OFF);
// Disable Code Protection
_FGS(GCP_OFF);            							

/* Program the Timer1 peripheral to raise interrupts */
void T1_program(void)
{
	T1CON = 0;		/* Stops the Timer1 and reset control reg	*/
	TMR1  = 0;		/* Clear contents of the timer register	*/
	PR1   = 0x9c40;		/* Load the Period register wit the value 0x9c40 (1ms @ 40MIPS)	*/
	IPC0bits.T1IP = 5;	/* Set Timer1 priority to 1		*/
	IFS0bits.T1IF = 0;	/* Clear the Timer1 interrupt status flag	*/
	IEC0bits.T1IE = 1;	/* Enable Timer1 interrupts		*/
	T1CONbits.TON = 1;	/* Start Timer1 with prescaler settings at 1:1
	 * and clock source set to the internal
	 * instruction cycle			*/
}

/* Clear the Timer1 interrupt status flag */
void T1_clear(void)
{
	IFS0bits.T1IF = 0;
}

/* This is an ISR Type 2 which is attached to the Timer 1 peripheral IRQ pin
 * The ISR simply calls CounterTick to implement the timing reference
 */
ISR2(_T1Interrupt)
{
	/* clear the interrupt source */
	T1_clear();

	/* count the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}

unsigned char lcd1[LCD_WIDTH];
unsigned char lcd2[LCD_WIDTH];

TASK(TaskScan)
{
	EE_lcd_putc('G');
	EE_lcd_putc('O');
	EE_lcd_putc(':');

	while (1) {
		EE_lcd_putc(EE_bluetooth_receive());
	}
}

TASK(TaskInit)
{
	EE_lcd_puts("BT Init...");

	// Init UART
	//EE_UART2_Init(38400, BIT8_NO | BIT_STOP_1, CTRL_SIMPLE);

	//Bluetooth initialization

	if (EE_bluetooth_init(2, 115200, BIT8_NO | BIT_STOP_1, CTRL_SIMPLE) == 0) {
		EE_lcd_puts("Done");
		/* Program cyclic alarms which will fire after an initial offset, and after that periodically */
		SetRelAlarm(AlarmScan,  2000, -1);
	} else {
		EE_lcd_puts("Fail");
	}
}

void InitLCD(void)
{
	EE_lcd_init();
	EE_lcd_clear();
	EE_lcd_home();
}

int main(void)
{
	/* Clock setup */
	CLKDIVbits.DOZEN   = 0;
	CLKDIVbits.PLLPRE  = 0;
	CLKDIVbits.PLLPOST = 0;
	PLLFBDbits.PLLDIV  = 78;

	/* Wait for PLL to lock */
	while(OSCCONbits.LOCK!=1);

	/* Program Timer 1 to raise interrupts */
	T1_program();

	/* Init LCD */
	InitLCD();

	ActivateTask(TaskInit);

	/* Forever loop: background activities (if any) should go here */
	for (;;);

	return 0;
}
