#include <stdio.h>

struct _stuff {
  unsigned int bitfields:1; // bit0
  unsigned int bit1:1;
  unsigned int bit2:1;
  unsigned int bit3:1;
  int i;
} stuff;

int main(int argc, char *argv[]) {
  stuff.bitfields = 1;
  stuff.bit1 = 0;
  stuff.bit2 = 1;
  stuff.bit3 = 0;
  stuff.i = 999;
  
  int i;
  
  for (i = 0; i < 4; i++)
  {
  	printf("#### %d\n", (&stuff.bitfields)[i]);
  }
  
  //printf("%d-%d-%d-%d-%d\n", stuff.bit1, stuff.bit2, stuff.bit3, stuff.bit4, stuff.i);
  return 0;
}