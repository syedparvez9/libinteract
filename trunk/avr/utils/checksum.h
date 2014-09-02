/*
 * checksum.h
 *
 * Implements a simple checksum. Useful for integrity checks. Uses a simple modular sum
 * as the checksum algorithm.
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
#ifndef CHECKSUM_H_
#define CHECKSUM_H_

/**
 * Generates a checksum for a piece of data. An optional argument #initChecksum# can be specified
 * to provide a better scramble of the data.
 */
inline unsigned char checksum(const unsigned char *data, size_t n,
                       unsigned char initChecksum = 0)
{
  unsigned char cs = initChecksum;
  while (n--)
    cs += *data++;
  return ((~cs) + 1); // two's complement
}

/**
 * Return true iff the received checksum corresponds to the expected one.
 */
inline bool verifyChecksum(unsigned char expectedChecksum,
                    const unsigned char *data, size_t n, 
                    unsigned char initChecksum = 0)
{
  expectedChecksum += initChecksum;
  while (n--)
    expectedChecksum += *data++;
  return (expectedChecksum == 0);
}

#endif /* CHECKSUM_H_ */
