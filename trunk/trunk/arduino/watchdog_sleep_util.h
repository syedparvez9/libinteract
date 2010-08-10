/*
 * watchdog_sleep_util.h
 * 
 * Provides utility functions for sleeping additional sleeping modes using the watchdog.
 *
 * (c) 2008 Sofian Audry | info(@)sofianaudry(.)com
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
#ifndef WATCHDOG_SLEEP_UTIL_INC
#define WATCHDOG_SLEEP_UTIL_INC

#include "WProgram.h"
#include <avr/sleep.h>
#include <avr/wdt.h>

//volatile boolean __f_wdt=1; //////// ??????? WTF

#define WATCHDOG_SLEEP_16MS    0
#define WATCHDOG_SLEEP_32MS    1
#define WATCHDOG_SLEEP_64MS    2
#define WATCHDOG_SLEEP_128MS   3
#define WATCHDOG_SLEEP_250MS   4
#define WATCHDOG_SLEEP_500MS   5
#define WATCHDOG_SLEEP_1S      6
#define WATCHDOG_SLEEP_2S      7
#define WATCHDOG_SLEEP_4S      8
#define WATCHDOG_SLEEP_8S      9

//****************************************************************
// 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms
// 6=1 sec,7=2 sec, 8=4 sec, 9= 8sec
void setupWatchDog(int ii) {

  byte bb;
  int ww;
  if (ii > 9) ii=9;
  bb = ii & 7;
  if (ii > 7) bb |= (1<<5);
  bb |= (1<<WDCE);
  ww = bb;

  MCUSR &= ~(1<<WDRF);
  // start timed sequence
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  // set new watchdog timeout value
  WDTCSR = bb;
  WDTCSR |= _BV(WDIE);
}

//****************************************************************  
// Watchdog Interrupt Service / is executed when watchdog timed out
ISR(WDT_vect) {
//  __f_wdt=1;  // set global flag
}

void sleepPowerDown() {
  // Sleep mode is set here.
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  // Enables the sleep bit in the mcucr register so sleep is possible.
  // Just a safety pin.
  sleep_enable();
  
  // Here the device is actually put to sleep!!
  // THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP
  sleep_cpu();
  
  // First thing after waking from sleep: disable sleep...
  sleep_disable();
}

#endif
