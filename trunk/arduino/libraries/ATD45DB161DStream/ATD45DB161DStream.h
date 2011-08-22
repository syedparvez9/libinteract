/*
 * ATD45DB161DStream.h
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

#ifndef AT45DB161DSTREAM_H_
#define AT45DB161DSTREAM_H_

#include "SeekableStream.h"
#include "at45db161d.h"

#define ATD45DB161D_BYTES_PER_PAGE 528
#define ATD45DB161D_N_PAGES        4096
#define ATD45DB161D_SIZE           2162688L // = BYTES_PER_PAGE * N_PAGES

class ATD45DB161DStream : public ATD45DB161D, public SeekableStream {
public:
  unsigned long curr;
  int bufferPage;  // Page of the current buffer.
  bool bufferIsSync; // true iff buffer is sync with data on chip.
  bool continuousArrayReadNeedsReset;
//  bool outputBufferEmpty;
//  bool writeMode;

  ATD45DB161DStream();

  void begin(uint8_t csPin=SLAVESELECT, uint8_t resetPin=RESET, uint8_t wpPin=WP);
//  void end();

  // From Print.h
  virtual void write(uint8_t x);

  // From Stream.h
  virtual int available();
  virtual int read();
  virtual int peek();
  virtual void flush();

  virtual void flushOutput();

  // From SeekableStream.h
  virtual unsigned long tell();
  virtual void seek(unsigned long pos, uint8_t origin = SEEK_SET);
  virtual bool eof();

  int currentPage() const;
  int currentOffset() const;
};

#endif /* AT45DB161DSTREAM_H_ */
