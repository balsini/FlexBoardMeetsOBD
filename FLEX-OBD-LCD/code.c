/*
 * code.h
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#include "ee.h"
#include "ee_irq.h"
#include "ee_bluetooth.h"
#include "LCD.h"
#include "mainFSM.h"
#include "buttons.h"
#include "constants.h"

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
	CounterTick(mainCounter);
	CounterTick(updateLCDCounter);
	CounterTick(receiveVehicleDataCounter);
}

TASK(TaskMain)
{
	mainFSM_dispatch();
}

TASK(TaskReceiveVehicleData) {}

TASK(TaskUpdateLCD) {}

int main(void)
{
	/* Clock setup */
	CLKDIVbits.DOZEN   = 0;
	CLKDIVbits.PLLPRE  = 0;
	CLKDIVbits.PLLPOST = 0;
	PLLFBDbits.PLLDIV  = 78; // 78

	/* Wait for PLL to lock */
	while(OSCCONbits.LOCK!=1);

	/* Program Timer 1 to raise interrupts */
	T1_program();

	/* Init LCD, buttons and Finite State Machine */
	LCD_init();
	LCD_appendR("  Flex2OBD 0.1");
	LCD_appendR("InitializingFlex");
	buttons_init();
	mainFSM_init();

	/* Program cyclic alarms which will fire after an initial offset, and after that periodically */
	SetRelAlarm(TaskMain, 1000, 150);

	//ActivateTask(TaskInit);

	/* Forever loop: background activities (if any) should go here */
	for (;;) ;

	return 0;
}
