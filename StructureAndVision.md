# Ideas #

First I suggest put all of the ideas we had when creating our code.

Here were mine:
  * Simple standalone include files (.h) to be cut-pasted in your Arduino code (not Arduino libraries, just .h, for simplicity)
  * AVR-compatible when relevant but targeted for Arduino (80% of the time you only need ATMega8/168)
  * Mostly class-based
  * Provide **simple** tools for simple apps (e.g. see TouchSensor.h) goal = replace complex/expensive circuits by simple circuits/cheap circuits with open source code

# What we got #

  * Tool classes to cope for Arduino's lacks: Timer.h, Random.h, PseudoAnalogWrite.h, analog\_reference.h, general.h, prescaler.h, printFloat.h
  * Utility classes for Arduino: oscilloscope.h
  * Sensor classes for Arduino: TouchSensor.h/VoltageMeter.h
  * Statistics/data classes: avr/math/`*`.h
  * Software reset (don't know how to categorize this): avr/softreset.h