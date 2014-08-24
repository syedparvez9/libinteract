/*
 * softreset.h
 *
 * Allows resetting the AVR from inside the program (ie. software reset).
 * Uses the watchdog timer.
 * 
 * IMPORTANT: Does NOT work if the bootloader is on the chip. You need to
 * erase the Arduino bootloader if you want to use this program.
 *
 * NOTE: including this file adds a file in the initialization process
 * that turns off the watchog timer early on system startup. To avoid that,
 * define the macro DISABLE_SOFTRESET_INIT during compilation (with gcc, just
 * add the flag -DDISABLE_SOFTRESET_INIT).
 * 
 * (c) 2008 Sofian Audry | info(@)sofianaudry(.)com
 *
 * This class was adapted from the files Random.{h,cc} in the Torch 
 * library (http://torch.ch)
 * Copyright (C) 2003--2004 Ronan Collobert | collober(@)idiap(.)ch
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef SOFTRESET_INC
#define SOFTRESET_INC

#include <avr/wdt.h>

uint8_t mcusr_mirror __attribute__ ((section (".noinit")));

// Turns off the watchdog early on system startup, thus preventing it
// to remain active on newer devices.
// Refer to <avr/wdt.h> for further details.
#ifndef DISABLE_SOFTRESET_INIT
void _softreset_init(void) \
  __attribute__((naked)) \
  __attribute__((section(".init3")));
void _softreset_init(void)
{
  mcusr_mirror = MCUSR;
  MCUSR = 0;
  wdt_disable();
}
#endif

/**
 * Resets the AVR.
 */
void softwareReset() {
  wdt_enable(WDTO_15MS);
  while (true);
}

/**
 * Access functions. Allow the user to know what was the cause of the
 * last reset.
 */
bool resetWasWatchdog() { return (mcusr_mirror & _BV(WDRF)); }
bool resetWasBrownOut() { return (mcusr_mirror & _BV(BORF)); }
bool resetWasExternal() { return (mcusr_mirror & _BV(EXTRF)); }
bool resetWasPowerOn() { return (mcusr_mirror & _BV(PORF)); }


#endif
