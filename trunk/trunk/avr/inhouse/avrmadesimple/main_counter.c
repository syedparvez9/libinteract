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
#include <util/delay.h>
#include "pin_macros.h"
int i;
#define MAXVAL 0xFFF

int main (void)
{
	//d0_input;	//initialize switch pin
	b0_output;
	b1_output;	//initialize LED pin
	b2_output;
	b3_output;
	b4_output;
	b5_output;
	b6_output;
	
	for (;;)
	{
		if ((i & 0x01) == 0x01) { b0_low; } else { b0_high; }
		if ((i & 0x02) == 0x02) { b1_low; } else { b1_high; }
		if ((i & 0x04) == 0x04) { b2_low; } else { b2_high; }
		if ((i & 0x08) == 0x08) { b3_low; } else { b3_high; }
		if ((i & 0x10) == 0x10) { b4_low; } else { b4_high; }
		if ((i & 0x20) == 0x20) { b5_low; } else { b5_high; }
		if ((i & 0x40) == 0x40) { b6_low; } else { b6_high; }
		if ((i & 0x80) == 0x80) { b7_low; } else { b7_high; }
		
		_delay_ms(1000);
		i = (i + 1) % MAXVAL;
	}
	
	return 0;
}
