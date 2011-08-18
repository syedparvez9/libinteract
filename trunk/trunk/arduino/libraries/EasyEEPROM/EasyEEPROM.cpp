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
#include "EasyEEPROM.h"

EasyEEPROM::EasyEEPROM() : _idx(-1), _sizeOfItem(0), _length(0) {} // dummy

bool EasyEEPROM::allocate(size_t sizeOfItem, size_t nItems) {
  if (!isNull())
    return false;
  _idx = EasyEEPROM::_allocate(sizeOfItem * nItems);
  _sizeOfItem = sizeOfItem;
  _length = nItems;
  return true;
}

bool EasyEEPROM::read(void *ptr) {
  if (isNull())
    return false;
  
  int endIdx = _idx + _sizeOfItem * _length;
  
  unsigned char *bptr = (unsigned char*)ptr;
  for (int i = _idx; i < endIdx; i++)
    *bptr++ = EEPROM.read(i);
  
  return true;
}

bool EasyEEPROM::readAt(int index, void *ptr) {
  if (isNull() || index >= _length)
    return false;
  
  int startIdx =_idx + (index*_sizeOfItem);
  int endIdx = startIdx + _sizeOfItem;

  unsigned char *bptr = (unsigned char*)ptr;
  for (int i = startIdx; i < endIdx; i++)
    *bptr++ = EEPROM.read(i);
    
  return true;
}

bool EasyEEPROM::write(const void *ptr) {
  if (isNull())
    return false;
  
  int endIdx = _idx + _sizeOfItem * _length;
  
  unsigned char *bptr = (unsigned char*)ptr;
  for (int i = _idx; i < endIdx; i++)
    EEPROM.write(i, *bptr++);
  
  return true;
}

bool EasyEEPROM::writeAt(int index, const void *ptr) {
  if (isNull() || index >= _length)
    return false;
  
  int startIdx = _idx + (index*_sizeOfItem);
  int endIdx = startIdx + _sizeOfItem;

  unsigned char *bptr = (unsigned char*)ptr;
  for (int i = startIdx; i < endIdx; i++)
    EEPROM.write(i, *bptr++);
    
  return true;
}

unsigned int EasyEEPROM::_allocate(size_t s) {
  if (currentIdx + s > EEPROM_SIZE)
    return (-1); // null
  unsigned int tmp = currentIdx;
  currentIdx += s;
  return tmp;
}

unsigned int EasyEEPROM::currentIdx = 0;
