/*
 * PseudoAnalogWrite.h
 * Allows to simulate a PWM on any digital output by quickly switching the pin
 * value from HIGH to LOW with a duty cycle proportional to the target value.
 * Works very well with LEDs and piezzo/speakers (to generate square sound waves).
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
#ifndef PSEUDO_ANALOG_INC
#define PSEUDO_ANALOG_INC

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

/**
 * Simulates analogWrite(pin, value) for a given time in milliseconds.
 * After the call, the value of the pin is restored to its initial state.
 * 
 * Example of use:
 * analogWrite(11, 126, 1000); // equivalent to:
 *                             // analogWrite(11, 126); 
 *                             // delay(1000);
 */
void pseudoAnalogWrite(byte pin, byte value, unsigned long time) {
  byte startValue = digitalRead(pin); // read the starting value of the pin iot restore it after
  if (value == 0) {
    digitalWrite(pin, LOW);
    delay(time);
  } else if (value == 255) {
    digitalWrite(pin, HIGH);
    delay(time);
  } else {
    unsigned long startTime = millis();
    while (millis() - startTime < time) {
      digitalWrite(pin, HIGH);
      delayMicroseconds(value);
      digitalWrite(pin, LOW);
      delayMicroseconds(255-value);
    }
  }
  digitalWrite(pin, startValue); // rewrite start value
}

void pseudoAnalogWrite(const byte *pins, byte value, unsigned long time, unsigned int nPins) {
  if (value == 0) {
    for (int i=0; i<nPins; i++)
      digitalWrite(pins[i], LOW);
    delay(time);
  } else if (value == 255) {
    for (int i=0; i<nPins; i++)
      digitalWrite(pins[i], HIGH);
    delay(time);
  } else {
    unsigned long startTime = millis();
    while (millis() - startTime < time) {
      for (int i=0; i<nPins; i++)
        digitalWrite(pins[i], HIGH);
      delayMicroseconds(value);
      for (int i=0; i<nPins; i++)
        digitalWrite(pins[i], LOW);
      delayMicroseconds(255-value);
    }
  }
  for (int i=0; i<nPins; i++)
    digitalWrite(pins[i], LOW);
}

#endif
