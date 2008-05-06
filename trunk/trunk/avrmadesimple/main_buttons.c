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
	d0_input;
	d1_input;
	d2_input;
	d3_input;
	d4_input;
	d5_input;
	d6_input;
	d7_input;
	
	b0_output;
	b1_output;
	b2_output;
	b3_output;
	b4_output;
	b5_output;
	b6_output;
	b7_output;
	
	//LED is off
	b0_high;
	b1_high;
	b2_high;
	b3_high;
	b4_high;
	b5_high;
	b6_high;
	b7_high;
	
	for (;;)
	{
		//check to see if pin d0 is low; if switch is pressed
		if (bit_is_clear(PIND,0)) { b0_low; } else { b0_high; }
		if (bit_is_clear(PIND,1)) { b1_low; } else { b1_high; }
		if (bit_is_clear(PIND,2)) { b2_low; } else { b2_high; }
		if (bit_is_clear(PIND,3)) { b3_low; } else { b3_high; }
		if (bit_is_clear(PIND,4)) { b4_low; } else { b4_high; }
		if (bit_is_clear(PIND,5)) { b5_low; } else { b5_high; }
		if (bit_is_clear(PIND,6)) { b6_low; } else { b6_high; }
		if (bit_is_clear(PIND,7)) { b7_low; } else { b7_high; }
	}
	
	return 0;
}
