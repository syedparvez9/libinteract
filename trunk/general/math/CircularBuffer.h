/*
 * CircularBuffer.h
 *
 * Manages integer data in a circular buffer.
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
#ifndef CIRCULAR_BUFFER_INC
#define CIRCULAR_BUFFER_INC

#include <stdlib.h>

class CircularBuffer {
  int *_buffer;
  int _capacity;
  int _size;
  int _index;

public:
  // Creates a new buffer with a maximum size of #capacity# elements.
  CircularBuffer(int capacity) {
    _capacity = capacity;
    _buffer = (int*) malloc(_capacity * sizeof(int));
    reset();
  }
 
 ~CircularBuffer() {
   free(_buffer);
 }
 
 // Resets the buffer.
  void reset() {
    _size = 0;
    _index = -1;
  }
  
  // Adds a value to the buffer.
  void push(int value) {
    // Reset index.
    if (_index == _capacity-1)
      _index = -1;
    
    // Set value.
    _buffer[++_index] = value;

    // Increase size if needed.
    if (_size < _capacity)
      _size++;
  }
  
  int size() const { return _size; }
  int capacity() const { return _capacity; }
  
  /*
   * get(0) returns the value that was last added
   * get(-1) returns the value that was added just before
   * Note that since this is a circular buffer: get(i) == get(i + size()) 
   */
  int get(int i) {
    i = _index + i;
    while (i < 0) i += _size;
    return _buffer[i % _size];
  }
  
  int *buffer() const { return _buffer; }
};

#endif
