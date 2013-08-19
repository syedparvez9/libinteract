/*
 * VoltageMeter.cpp
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
 
#include "VoltageMeter.h"

VoltageMeter::VoltageMeter(byte pin, float vMax, byte analogRef)
  : _pin(pin), _analogReference(analogRef), _vMax(vMax)
 {}

VoltageMeter::VoltageMeter(byte pin, float rGndToPin, float rPinToVcc, byte analogRef, float vRef)
: _pin(pin), _analogReference(analogRef)
{
  _vMax = resistorsToVoltage(rGndToPin, rPinToVcc, vRef);
}

float VoltageMeter::resistorsToVoltage(float rGndToPin, float rPinToVcc, float vRef) {
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
    return vRef * (rGndToPin + rPinToVcc) / rGndToPin;
  }

  float VoltageMeter::analogReadVoltage(int nSamples) const {
    byte currentReference = getAnalogReference();
    if (currentReference != _analogReference)
      setAnalogReference(_analogReference);

    float sum = 0;
    for (int i=0; i< nSamples; i++)
      sum += analogRead(_pin);

    if (currentReference != _analogReference)
      setAnalogReference(currentReference);

    return (sum / nSamples);
  }

  float VoltageMeter::voltage(int nSamples) const {
    return ((float)analogReadVoltage(nSamples)) / 1023.0f * _vMax;
  }
