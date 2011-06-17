/*
 * availableMemory.h
 *
 * Returns the number of bytes currently free in RAM
 * 
 * (c) 2011 Sofian Audry | info(@)sofianaudry(.)com
 *
 * Based on code written David A. Mellis
 * Based on code by Rob Faludi http://www.faludi.com
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
#ifndef AVAILABLE_MEMORY_INC
#define AVAILABLE_MEMORY_INC

#include <cstdlib.h>

// this function will return the number of bytes currently free in RAM
size_t availableMemory() {
  unsigned char *buf;
  size_t size = 0;
  while ( (buf = (unsigned char*) malloc(size)) != NULL) {
    size++;
    free(buf);
  }
  free(buf);
  return size;
}


