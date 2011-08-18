/*
 * EasyEEPROM class
 * Makes working with EEPROM easy by providing memory reservation and
 * read/write functionalities
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
#ifndef EASY_EEPROM_INC
#define EASY_EEPROM_INC

#include "WProgram.h"

#include <stddef.h> // for size_t

#include <EEPROM.h>

// TODO: recoder directement avec eeprom.h eg. eeprom_read_word et eeprom_read_block

#ifndef EEPROM_SIZE
#if defined(__AVR_ATmega8__) || defined(__AVR_ATmega168__)
#define EEPROM_SIZE 512
#elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)
#define EEPROM_SIZE 1024
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#define EEPROM_SIZE 4096
#else
#error "Unsupported processor (please define the EEPROM_SIZE for your specific architecture)
#endif
#endif

class EasyEEPROM {
  
  static unsigned int currentIdx;
  
  unsigned int _idx;
  size_t _sizeOfItem;
  size_t _length; // number of items
  
public:
  EasyEEPROM();
  bool allocate(size_t sizeOfItem, size_t nItems = 1);
  
  bool isNull() const { return (_idx == -1); }
  bool isArray() const { return (_length > 1); }
  
  size_t sizeOfItem() const { return _sizeOfItem; }
  size_t length() const { return _length; }
  size_t size() const { return _length * _sizeOfItem; }
  
  bool read(void *ptr);
  
  bool readAt(int index, void *ptr);
  
  bool write(const void *ptr);
  
  bool writeAt(int index, const void *ptr);
  
  static size_t allocated() {
    return (size_t) currentIdx;
  }

  static size_t available() {
    return (size_t) (EEPROM_SIZE - currentIdx);
  }
  
protected:
  unsigned int _allocate(size_t s);
/*
  void writeAt(int index, byte v) {
    writeAt(index, &v);
  }
  
  void writeAt(int index, int v) {
    writeAt(index, &v);
  }

  void writeAt(int index, float v) {
    writeAt(index, &v);
  }
  
  byte readByte() {
    byte v;
    read(&v);
    return v;
  }

  char readChar() {
    char v;
    read(&v);
    return v;
  }

  bool readBool() {
    return (bool) readByte();
  }
  
  int readInt() {
    int v;
    read(&v);
    return v;
  }
  
  int readFloat() {
    float v;
    read(&v);
    return v;
  }

  int readDouble() {
    double v;
    read(&v);
    return v;
  }*/
};

#endif