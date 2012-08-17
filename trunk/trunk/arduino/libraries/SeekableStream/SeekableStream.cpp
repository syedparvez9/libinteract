/**
 * SeekableStream.h
 *
 * This class adds seek/peek functionalities to Stream. It is useful for addressable
 * memories such as EEPROM, dataflash or SD cards.
 *
 * The idea was introduced in the following forum post:
 * http://arduino.cc/forum/index.php/topic,69584.0.html
 *
 * (c) 2011 Sofian Audry -- info(@)sofianaudry(.)com
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

#include "SeekableStream.h"

size_t SeekableStream::read(uint8_t *buf, size_t size)
{
  size_t av = available();
  if (size > av) size = av;
  if (size == 0) return 0;
  for (int i=0; i<size; i++)
    *buf++ = (uint8_t) read();
  return size;
}