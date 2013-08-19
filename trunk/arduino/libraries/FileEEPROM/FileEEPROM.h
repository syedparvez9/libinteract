/*
 * FileEEPROM
 * Library that makes working with EEPROM easy by providing file-like access
 * through routines similar to the ones in <stdio> (fread, fwrite, etc)
 *
 * (c) 2011 Sofian Audry | info(@)sofianaudry(.)com
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
#ifndef FILE_EEPROM_INC
#define FILE_EEPROM_INC

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#ifndef EEPROM_SIZE
#if defined(__AVR_ATmega8__) || defined(__AVR_ATmega168__)
#define EEPROM_SIZE 512
#elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)
#define EEPROM_SIZE 1024
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#define EEPROM_SIZE 4096
#else
#error "Unsupported processor (please define the EEPROM_SIZE for your specific architecture)"
#endif
#endif

class MyFileEEPROM {
  int pos;
  
public:
  MyFileEEPROM() : pos(0) {}
    
  // Read something.
  int read(void *ptr, int blockSize = 1, int nBlocks = 1);
  
  // Write.
  int write(const void *ptr, int blockSize = 1, int nBlocks = 1);
  int eof();
  int seek(int offset/*, int whence*/);
  
  // Tell where I am.
  int tell();
  
  // Rewind to the start
  void rewind();
};

extern MyFileEEPROM FileEEPROM;

#endif
