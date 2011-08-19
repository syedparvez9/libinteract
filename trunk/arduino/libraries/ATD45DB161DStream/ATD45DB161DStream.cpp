/*
 * ATD45DB161DStream.cpp
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

#include "ATD45DB161DStream.h"

ATD45DB161DStream::ATD45DB161DStream() :
  curr(0), bufferPage(-1), bufferIsSync(false)
{
}

void ATD45DB161DStream::begin(uint8_t csPin, uint8_t resetPin, uint8_t wpPin) {
  /* Make sure SPI is initialized */
  SPI.begin();

  /* Let's wait 1 second, allowing use to press the serial monitor button :p */
  delay(1000);

  /* Initialize dataflash */
  ATD45DB161D::begin(csPin, resetPin, wpPin);
}

void ATD45DB161DStream::write(uint8_t x) {
  if (bufferPage != currentPage()) {
    // Fill buffer with current data from the page in order to preserve it.
    BufferRead(1, 0, 1); // TODO: why low speed (third arg) ?
    bufferPage = currentPage();
    bufferIsSync = true;
  }

//  // Switch check.
//  else if (!writeMode) {
//    // Because we have previously switched to read mode, we now need to re-read the buffer.
//
//    writeMode = true;
//  }

  /* Set dataflash so that any call to spi_tranfer will write the byte
   * given as argument to the Buffer 1 */
  BufferWrite(1, currentOffset());

  // Transfer data to buffer.
  SPI.transfer(x);

  // Output
  bufferIsSync = false;

  // End of page check.
  if (currentOffset() == ATD45DB161D_BYTES_PER_PAGE-1) {
    // Send buffer to dataflash.
    flushOutput();
  }
  curr++;
}

// From Stream.h
int ATD45DB161DStream::available() {
  // there's actually much more available but we're limited by the library (int)
  return (int) min(ATD45DB161D_SIZE - curr, 32767);
}

int ATD45DB161DStream::read() {
  int val = peek();
  curr++;
  return val;
}

int ATD45DB161DStream::peek() {
  flushOutput();
  ReadMainMemoryPage(currentPage(), currentOffset());
  return SPI.transfer(0xff);
}

void ATD45DB161DStream::flush() {
  // Nothing to do here.
}

void ATD45DB161DStream::flushOutput() {
  if (!bufferIsSync) {
    Serial3.print("Flushing to page: "); Serial3.println(currentPage());
    BufferToPage(1, currentPage(), 1);
    bufferIsSync = true;
  }
}

unsigned long ATD45DB161DStream::tell() {
  return curr;
}

void ATD45DB161DStream::seek(unsigned long pos/*, int dir = CUR*/) {
  flushOutput(); // Flush buffer.
  curr = min(pos, ATD45DB161D_SIZE); // cannot seek over max size
}

bool ATD45DB161DStream::eof() {
  return (curr >= ATD45DB161D_SIZE);
}

int ATD45DB161DStream::currentPage() const {
  return (curr / ATD45DB161D_BYTES_PER_PAGE);
}

int ATD45DB161DStream::currentOffset() const {
  return (curr % ATD45DB161D_BYTES_PER_PAGE);
}
