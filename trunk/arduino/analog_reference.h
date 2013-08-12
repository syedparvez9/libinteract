/*
 * analog_reference.h
 * 
 * Include file that defines/implements methods to deal with analog reference
 * on the Arduino board. The analogReference() method in the Arduino library
 * is based on the assumption that the analog reference will not be changed during
 * the course of the program. Doing can actually result in errors.
 * 
 * WARNING: Be cautious when changing the analog reference, especially if you are
 * using AREF, as connecting AREF to a voltage source might result in a short circuit
 * if you switch to internal reference. See ATmega8/168 manual for details.
 *
 * (c) 2008 Sofian Audry | info((@))sofianaudry((.))com
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
#ifndef ANALOG_REFERENCE_INC
#define ANALOG_REFERENCE_INC

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "prescaler.h"

#define ANALOG_REFERENCE_DUMMY_PIN 0

/**
 * Returns the actual value of analog reference (either DEFAULT, INTERNAL or EXTERNAL).
 * Calls analogRead() to set ADMUX.
 */
static uint8_t getAnalogReference() {
  // Makes sure mode has been set in ADMUX by calling analogRead() on method's first call
  analogRead(ANALOG_REFERENCE_DUMMY_PIN);
  
  return (ADMUX >> 6);
}

/**
 * Replacement method for analogReference(). Makes sure the next call to analogRead() will
 * return the right value. Calls analogRead().
 */
static void setAnalogReference(byte mode) {
  analogReference(mode);                   // switch to new reference
  
  // XXX I don't know why but without these lines the switch from 
  // DEFAULT to INTERNAL does not work well.
  analogRead(ANALOG_REFERENCE_DUMMY_PIN);
  trueDelay(100); // wait for 100 ms
}

/**
 * Returns the analog value at #pin# by using the analog reference mode specified
 * by #mode#. Switches back to original mode after.
 * Optional argument #nSamples# allows to ask for an average value over many samples.
 * Optional argument #timeBetweenSamples# allows to set a delay (in milliseconds) between each reading.
 */
static int analogReadReference(byte pin, byte mode, int nSamples = 1, unsigned long timeBetweenSamples = 0) {

  uint8_t currentReference = getAnalogReference(); // copy current reference
  setAnalogReference(mode);                        // safely switch to new reference

  int value;

  if (nSamples == 1)
    value = analogRead(pin);

  else {
    unsigned long sum = 0;
    if (timeBetweenSamples > 0)
      for (int i=0; i<nSamples; i++) {
        sum += analogRead(pin);
        delay(timeBetweenSamples);
      }
    else
      for (int i=0; i<nSamples; i++)
        sum += analogRead(pin);

    value = (int) (sum / nSamples);
  }

  setAnalogReference(currentReference);   // switch back to original reference

  return (value);
}

#endif
