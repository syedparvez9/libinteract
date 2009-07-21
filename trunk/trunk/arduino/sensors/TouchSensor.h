/*
 * TouchSensor.h
 *
 * A simple touch sensor based on human capacitance. See schematics and
 * usage below.
 * 
 * (c) 2008 Sofian Audry | info(@)sofianaudry(.)com
 *
 * This code was adapted from a technique by Pontus Frössander described at
 * http://www.e.kth.se/~pontusf/touchsensor.html
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
#ifndef TOUCH_SENSOR_INC
#define TOUCH_SENSOR_INC

/*

Circuit schematics
------------------


                ~0.5 M 
  SEND PIN ----/\/\/\----*
                         |
  RECEIVE PIN -----------*------------- SENSOR
                         |
                         = 100 pF
                         |
                        GND

The sensor is a simple copper plate, with or without insulation.
The resistor has to be chosen carefully; it is recommended to use an
~1M variable resistor and use it to adjust the sensitivity.
The 100pF capacitor can be dropped if the circuit is grounded, it is
especially recommended for battery-operated systems that are not plugged
to ground.

Example Arduino code
------------------------------
#include "TouchSensor.h"

#define SIGNAL_OUT 5
#define SIGNAL_IN 6

#define N_SAMPLES 8
#define THRESHOLD 0.2f

TouchSensor sensor(SIGNAL_OUT, SIGNAL_IN, N_SAMPLES);

void setup() {
  sensor.init();
  Serial.begin(9600);
}

void loop() {
  float s = sensor.sense();
  if (s >= THRESHOLD) {
    Serial.print("Touch: "); Serial.print(round(s*100)); Serial.println("%");
  }
}
  
*/
class TouchSensor {
  byte _sendPin;
  byte _receivePin;
  int _nSamples;
  
public:
  TouchSensor(byte sendPin, byte receivePin, int nSamples = 8)
    : _sendPin(sendPin), _receivePin(receivePin), _nSamples(nSamples) {}
    
  void init() {
    pinMode(_sendPin, OUTPUT);
    pinMode(_receivePin, INPUT);
  }
  
  boolean detect(float threshold = 0.5f) {
    return (sense() >= threshold);
  }
  
  boolean senseOne() {
    digitalWrite(_sendPin, LOW);
    delay(2);
    digitalWrite(_sendPin, HIGH);
    delayMicroseconds(5);
    return (digitalRead(_receivePin) != HIGH);
  }
  
  float sense() {
    float nTouches = 0;
    for (int i=0; i<_nSamples; i++) {
      if (senseOne())
         nTouches++;
    }
    return nTouches / (float)_nSamples;
  }
  
};

#endif
