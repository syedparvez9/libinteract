/*
 * TestATD45DB161DStream.pde
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

ATD45DB161DStream dataflash;

void setup() {
  uint8_t        status;
  ATD45DB161D::ID id;

  dataflash.begin(34);
  delay(10);

  /* Read status register */
  status = dataflash.ReadStatusRegister();

  /* Read manufacturer and device ID */
  dataflash.ReadManufacturerAndDeviceID(&id);

  /* Set baud rate for serial communication */
  Serial.begin(115200);

  /* Display status register */
  Serial.print("Status register :");
  Serial.print(status, BIN);
  Serial.print('\n');

  /* Display manufacturer and device ID */
  Serial.print("Manufacturer ID :\n");  // Should be 00011111
  Serial.print(id.manufacturer, HEX);
  Serial.print('\n');

  Serial.print("Device ID (part 1) :\n"); // Should be 00011111
  Serial.print(id.device[0], HEX);
  Serial.print('\n');

  Serial.print("Device ID (part 2)  :\n"); // Should be 00000000
  Serial.print(id.device[1], HEX);
  Serial.print('\n');

  Serial.print("Extended Device Information String Length  :\n"); // 00000000
  Serial.print(id.extendedInfoLength, HEX);
  Serial.print('\n');
}

void testReadWrite(long start, long size) {
  char str[30];
  unsigned char c = 0;
  dataflash.seek(start);
  for (int i=0; i<size; i++) {
    dataflash.write( c++ );
  }
  c = 0;
  // TODO: on devrait pas avoir besoin de tca
  dataflash.flushOutput();
  dataflash.seek(start);
  for (long i=0; i<size; i++) {
    int rd = dataflash.read();
//    Serial.print(i);
    if (rd != c) {
      sprintf(str, " Problem @ %lu read: %d, expected: %d", (long)(i+start), rd, c);
      Serial.println(str);
    }/* else
      Serial.println(" ok");*/
    c++;
  }
}

void loop() {

  Serial.println("Test 1: page write + read of one byte");

  Serial.println("Read/write A");
  dataflash.rewind(); // == dataflash.rewind();
  dataflash.write('A');
  dataflash.rewind();
  if (dataflash.peek() != 'A') {
    Serial.print("Error! read = ");
    Serial.println((char)dataflash.peek());
  }

  Serial.println("Read/write B");
  dataflash.write('B');
  dataflash.rewind();
  if (dataflash.peek() != 'B') {
    Serial.print("Error! read = ");
    Serial.println((char)dataflash.peek());
  }

  Serial.println("Test 2: page write + read of first 2 pages + one byte");
  testReadWrite(0, 2*ATD45DB161D_BYTES_PER_PAGE + 1);

  Serial.println("Test 3: page write + read of middle 2 pages + one byte");
  testReadWrite(((long)(100*(long)ATD45DB161D_BYTES_PER_PAGE)), 2*ATD45DB161D_BYTES_PER_PAGE + 1);

  Serial.println("Test 4: page write + read of end 2 pages - one byte");
  testReadWrite(ATD45DB161D_SIZE - 2*ATD45DB161D_BYTES_PER_PAGE - 1, 2*ATD45DB161D_BYTES_PER_PAGE);

  Serial.println("Test 5: limit test");
  Serial.println("Seeking at eof");
  dataflash.seek(ATD45DB161D_SIZE);
  Serial.print("Available = "); Serial.print(dataflash.available()); Serial.print(" --> ");
  Serial.println( (dataflash.available() == 0) ? "OK" :"ERROR");
  Serial.print("Peek = -1 test: "); Serial.println( (dataflash.peek() == -1) ? "OK" : "ERROR");
  Serial.println("Seeking at eof - 1");
  dataflash.seek(ATD45DB161D_SIZE-1);
  Serial.print("Available = "); Serial.print(dataflash.available()); Serial.print(" --> ");
  Serial.println( (dataflash.available() == 1) ? "OK" :"ERROR");
  Serial.print("Peek != -1 test: "); Serial.println( (dataflash.peek() != -1) ? "OK" : "ERROR");

  Serial.println("Test 6: write somewhere, write elsewhere, come back and read");
  // "Erase" first page
  dataflash.rewind();
  for (int i=0; i<ATD45DB161D_BYTES_PER_PAGE; i++)
    dataflash.write('#');
  // Write 'A'
  dataflash.rewind();
  dataflash.write('A');
  dataflash.seek(2000);
  dataflash.write('X');
  dataflash.rewind();
  int c = dataflash.read();
  if (c != 'A') {
    Serial.print("A ");
    Serial.print("Error! read = ");
    Serial.println((char)c);
  }
  for (int i=1; i<ATD45DB161D_BYTES_PER_PAGE; i++) {
    c = dataflash.read();
    if (c != '#') {
      Serial.print(i);
      Serial.print(" Error! read = ");
      Serial.println((char)c);
    }
  }



  delay(2000);
}
