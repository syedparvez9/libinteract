/*
 * VoltageMeter.h
 * 
 * A simple utility class to read voltage. Uses a simple voltage divider
 * and the internal analog reference.
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
#ifndef VOLTAGE_METER_INC
#define VOLTAGE_METER_INC

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "analog_reference.h"

/*

Circuit schematics
------------------

            R1             R2
  GND ----/\/\/\----*----/\/\/\---- Vin
                    |
                    | Vout
                    |
               ANALOG PIN

Vin  : input voltage (the voltage we try to meter)
Vmax : the maximum value of the input voltage
Vout : the output voltage (the Vin remapped to 0 .. 1.1V)

Choose R1 and R2 CAREFULLY according to the following rule:
R1 = R2 x 1.1 / (Vmax - 1.1)
R2 = R1 x (Vmax - 1.1) / 1.1

A typical configuration is R1 = 1k and R2 = 4k. It assumes Vmax = 5.5V.

*IMPORTANT NOTICES*
1) It is recommended to test the circuit before, especially if Vmax > 6V,
   to make sure the voltage at the analog pin (Vout) does not get over 5V.
2) Since this system relies on the internal reference, you should NOT
   connect any external voltage source to the AREF pin.
3) ATmega168 datasheet has the following notice "Note that VREF is a high 
   impedance source, and only a capacitive load should be connected in a 
   system." which means in other words that "when VREF is used as an output, 
   you may not draw current from it. You may connect a capacitor to it to 
   eliminate any ripple that might be caused by noise on adjacent circuits."
   (this precision was mentionned by Peter Pryor, thanks).

Example Arduino code
------------------------------
#include "VoltageMeter.h"

#define VOLTAGE_AIN 0

VoltageMeter meter(VOLTAGE_AIN, 5.5);

void setup() {
  Serial.begin(9600);
}

void loop() {
  float voltage = meter.voltage();
  Serial.print((int)(voltage*1000), DEC); Serial.println(" mV");
}
  
*/
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1284P__)
#define VOLTAGE_METER_DEFAULT_ANALOG_REFERENCE INTERNAL1V1
#else
#define VOLTAGE_METER_DEFAULT_ANALOG_REFERENCE INTERNAL
#endif

class VoltageMeter {
  byte _pin;
  byte _analogReference;
  float _vMax;
  
public:
  VoltageMeter(byte pin, float vMax, byte analogRef=VOLTAGE_METER_DEFAULT_ANALOG_REFERENCE)
    : _pin(pin), _analogReference(analogRef), _vMax(vMax)
  {}

  VoltageMeter(byte pin, float rGndToPin, float rPinToVcc, byte analogRef=VOLTAGE_METER_DEFAULT_ANALOG_REFERENCE, float vRef=-1)
    : _pin(pin), _analogReference(analogRef) {
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1284P__)
    if (_analogReference == INTERNAL1V1)
      vRef = 1.1f;
    else if (_analogReference == INTERNAL2V56)
      vRef = 2.56f;
    else if (vRef < 0)
      vRef = 5.5f; // default
#else
    if (_analogReference == INTERNAL)
      vRef = 1.1f;
    else if (vRef < 0)
      vRef = 5.5f; // default
#endif
    _vMax = vRef * (rGndToPin + rPinToVcc) / rGndToPin;
  }

  int analogReadVoltage(int nSamples = 1) const {
    byte currentReference = getAnalogReference();
    setAnalogReference(_analogReference);
    float sum = 0;
    for (int i=0; i< nSamples; i++)
      sum += analogRead(_pin);
    setAnalogReference(currentReference);
    return (sum / nSamples);
  }
  
  float voltage(int nSamples = 1) const {
    return ((float)analogReadVoltage(nSamples)) / 1023.0f * _vMax;
  }
};

#endif
