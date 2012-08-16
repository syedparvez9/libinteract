/*
 * prescaler.h
 *
 * Provides useful tools to manage the clock prescaler and issues
 * related to time and delays. Allows to easily set the prescaler
 * and get access to its value. Also provides alternative functions
 * to the millis() and delay() functions.
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
#ifndef PRESCALER_INC
#define PRESCALER_INC

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <avr/power.h>

inline uint16_t getClockDivisionFactor() {
  return ((uint16_t)(1 << clock_prescale_get()));
}

/**
 * Time in milliseconds. Actually uses the micros() function to achieve better resolution.
 *
 * NOTE: This is the equivalent of the millis() function but it readjusts it according
 * to the current clock division. As such, be careful of how you make use of it, in
 * particular remember it will be wrong if the clock division factor is changed during the
 * course of computation. Remember that you can reset the overflow counter by calling the
 * init() function from wiring.h.
 */
inline unsigned long trueMillis()
{
  uint16_t cdf = getClockDivisionFactor();
  // Same same.
  if (cdf == 1)
    return millis();
  // Don't use micros() if we're going to break the micros() resolution anyway.
  // See: http://www.arduino.cc/en/Reference/Micros
#if F_CPU >= 16000000L
  else if (cdf <= 4)
#else
  else if (cdf <= 8)
#endif
    return millis() * cdf;
  // Otherwise, use micros() instead of millis() as they will give more precision.
  else
    return  ( (uint32_t) (micros() * cdf) ) / 1000;
}

// Waits for #ms# milliseconds.
// NOTE: Please see comment above.
inline void trueDelay(unsigned long ms)
{
  unsigned long start = trueMillis();
  while (trueMillis() - start < ms);
}

/**
 * Rescales given delay time (in milliseconds or microseconds) according to division factor. 
 * Should be called before a call to delay(). Insures compatibility with function using delay().
 * Example use:
 * delay( rescaleDelay(1000) ); // equivalent to wait(1000)
 */
inline unsigned long rescaleDuration(unsigned long d) {
  return (d / getClockDivisionFactor());
}

/**
 * Rescales given time (in milliseconds or microseconds) according to division factor. Should
 * be called 
 */
inline unsigned long rescaleTime(unsigned long t) {
  return (t * getClockDivisionFactor());
}

#endif
