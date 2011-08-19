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

ATD45DB161DStream df;

void setup() {
  df.begin(5,6,7);
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

void loop() {
  char str[30];

  Serial.println("Test 1: page write + read of first 2 pages + one byte");
  unsigned char c = 0;
  df.rewind();
  for (int i=0; i<2*ATD45DB161D_BYTES_PER_PAGE + 1; i++) {
    df.write( c++ );
  }
  c = 0;
  for (int i=0; i<2*ATD45DB161D_BYTES_PER_PAGE + 1; i++) {
    int rd = df.read();
    if (rd != c) {
      sprintf(str, "Problem @ %d read: %d, expected: %d", i, rd, c);
      Serial.println(str);
      break;
    }
    c++;
  }
}
