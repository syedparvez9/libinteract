/*
Title:			sample_program.c
Author:			Leah Buechley
Date Created:   1/18/06
Last Modified:  1/18/06
Purpose: simple sample program.  
		 an LED, tied to pin b1, is on as long as a switch, tied to pin b0, is pressed
		 test out on the STK500 by tying b0 to LED0 and b1 to SW0
*/
//#define __AVR_ATmega8515__ is implicit !
#include <avr/io.h>
#include "pin_macros.h"

int main (void)
{
	d0_input;	//initialize switch pin
	b1_output;	//initialize LED pin
	
	b1_high;	//LED is off
	
	for (;;)
	{
		while (bit_is_clear(PIND,0))	//check to see if pin b0 is low; if switch is pressed
			b1_low;		//LED is on
			
		b1_high;		//LED is off
	}
	
	return 0;
}
