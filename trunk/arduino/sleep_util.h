/*
 * sleep_util.h
 * 
 * Provides utility functions for sleeping modes. 
 * NOTE: Currently only supports the "power down" mode.
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
#ifndef SLEEP_UTIL_INC
#define SLEEP_UTIL_INC

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <avr/sleep.h>

void sleepPowerDown(byte interrupt, void (*wakeUpFunction)(void) = 0) {
  // Sleep mode is set here.
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  // Enables the sleep bit in the mcucr register so sleep is possible.
  // Just a safety pin.
  sleep_enable();

  // Use interrupt and run function when pin gets LOW.
  attachInterrupt(interrupt, wakeUpFunction, LOW);
  
  // Here the device is actually put to sleep!!
  // THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP
  sleep_cpu();
  
  // First thing after waking from sleep: disable sleep...
  sleep_disable();
    
  // Disables interrupt so the wake up function code will not be executed
  // during normal running time.
  detachInterrupt(interrupt);
}

#endif
