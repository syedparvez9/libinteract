#include "FileEEPROM.h"
#include <avr/eeprom.h>

// Read something.
int MyFileEEPROM::read(void *ptr, int blockSize, int nBlocks) {
  nBlocks *= blockSize; // nBlocks becomes total memory (saves one int)
  if (pos + nBlocks > EEPROM_SIZE)
    return 0; // TODO: rendre compliant avec fread
  eeprom_read_block (ptr, (const void*) pos, nBlocks);
  pos += nBlocks;
}

// Write.
int MyFileEEPROM::write(const void *ptr, int blockSize, int nBlocks) {
  nBlocks *= blockSize; // nBlocks becomes total memory (saves one int)
  if (pos + nBlocks > EEPROM_SIZE)
    return 0; // TODO: rendre compliant avec fread
  eeprom_write_block (ptr, (void*) pos, nBlocks);
  pos += nBlocks;
}

int MyFileEEPROM::eof() {
  return (pos >= EEPROM_SIZE);
}

int MyFileEEPROM::seek(int offset/*, int whence*/) {
  pos = offset;
}

// Tell where I am.
int MyFileEEPROM::tell() {
  return pos;
}

// Rewind to the start
void MyFileEEPROM::rewind() {
  pos = 0;
}

MyFileEEPROM FileEEPROM;
