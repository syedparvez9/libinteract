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

// Tout ce qui est ici pourrait simplement être statique.
class EasyEEPROMLib {

  unsigned int currentIdx;
  
  public:
  EasyEEPROMLib() {
    reset();
  }
  
  void reset() {
    currentIdx = 0;
  }
  
  unsigned int malloc(size_t s) {
    if (currentIdx + s > EEPROM_SIZE)
      return (-1); // null
    unsigned int tmp = currentIdx;
    currentIdx += s;
    return tmp;
  }
  
  size_t allocated() {
    return (size_t) currentIndex;
  }

  size_t available() {
    return (size_t) (EEPROM_SIZE - currentIndex);
  }
  
};

EasyEEPROMLib EasyEEPROMAllocator;
class EasyEEPROM {
  
  unsigned int _idx;
  size_t _sizeOfItem;
  size_t _length; // number of items
  
public:
  EasyEEPROM() : _idx(-1), _sizeOfItem(0), _length(0) {} // dummy

  // NOTE: J'ai enleve pcq si on initialise hors de setup() (donc en construction) ca n'appele pas allocate() toujours au bon moment...
  /*  EasyEEPROM(size_t sizeOfItem, size_t nItems = 1) {
    allocate(sizeOfItem, nItems);
  }
  */
  
  bool allocate(size_t sizeOfItem, size_t nItems = 1) {
    if (!isNull())
      return false;
    _idx = EasyEEPROMAllocator.malloc(sizeOfItem * nItems);
    _sizeOfItem = sizeOfItem;
    _length = nItems;
    return true;
  }
  
  bool isNull() const { return (_idx == -1); }
  bool isArray() const { return (_length > 1); }
  
  size_t sizeOfItem() const { return _sizeOfItem; }
  size_t length() const { return _length; }
  size_t size() const { return _length * _sizeOfItem; }
  
  bool read(void *ptr) {
    if (isNull())
      return false;
    
    int endIdx = _idx + _sizeOfItem * _length;
    
    unsigned char *bptr = (unsigned char*)ptr;
    for (int i = _idx; i < endIdx; i++)
      *bptr++ = EEPROM.read(i);
    
    return true;
  }
  
  bool readAt(int index, void *ptr) {
    if (isNull() || index >= _length)
      return false;
    
    int startIdx =_idx + (index*_sizeOfItem);
    int endIdx = startIdx + _sizeOfItem;

    unsigned char *bptr = (unsigned char*)ptr;
    for (int i = startIdx; i < endIdx; i++)
      *bptr++ = EEPROM.read(i);
      
    return true;
  }
  
  bool write(const void *ptr) {
    if (isNull())
      return false;
    
    int endIdx = _idx + _sizeOfItem * _length;
    
    unsigned char *bptr = (unsigned char*)ptr;
    for (int i = _idx; i < endIdx; i++)
      EEPROM.write(i, *bptr++);
    
    return true;
  }
  
  bool writeAt(int index, const void *ptr) {
    if (isNull() || index >= _length)
      return false;
    
    int startIdx = _idx + (index*_sizeOfItem);
    int endIdx = startIdx + _sizeOfItem;

    unsigned char *bptr = (unsigned char*)ptr;
    for (int i = startIdx; i < endIdx; i++)
      EEPROM.write(i, *bptr++);
      
    return true;
  }
  
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