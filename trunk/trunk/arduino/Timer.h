/*
 * Timer class
 * Counts the time passed since started.
 * 
 * This is an object-oriented version of 
 * See http://accrochages.drone.ws/node/90
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
#ifndef TIMER_INC
#define TIMER_INC

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

/*
 * Example code:
 *
 * Timer myTimer;
 * // ...
 * myTimer.start(); // start timer
 * while (myTimer.currentTime() < 2000) // a 2000 ms loop
 *   // do something
 * myTimer.stop();      // stop timer
 * myTimer.start(1000); // start the timer at 1000 ms
 * // ...
 *
 * Alternatively the timer can be started at construction for shorter code:
 * Timer myTimer(true); // timer starts at once
 * while (myTimer.currentTime() < 2000)
 *   // ...
 */
class Timer {
  unsigned long _startTime;
  bool _started;

public:
  Timer(bool startNow = false) : _startTime(0), _started(false) {
    if (startNow)
      start();
  }
  
  void start() {
    _startTime = millis();
    _started = true;
  }
  
  void stop() {
    _started = false;
  }
  
  bool isStarted() {
    return _started;
  }
  
  unsigned long currentTime() {
    return (millis() - _startTime);
  }
  
};

#endif
