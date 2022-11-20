#include <stdlib.h>
#include <stdio.h>
#include <string.h>

uint8_t* skipHeader(uint8_t *ptr)
{
  //uint8_t * copy = ptr;
  while (*ptr != '2' && *(ptr + 1) != '5' && *(ptr + 2) != '5')
    ptr++;
  ptr += 7;
  //printf("skip %u\n", (uint32_t)ptr - (uint32_t)copy);
  return ptr;
  // P6 WIDTH HEIGHT MAXCOLOR <- extra space at end
}

#include "openFile.c"
#include "decrypt.c"

int main()
{
  printf("\
-----C-Steganography DECRYPTER-----\n\
For all file names do not put the extension\n\
  For example, for 'cow.ppm' type 'cow'\n\
-------------------------\n");
  char* filename = malloc(100);
  printf("file name: ");
  scanf("%s", filename);
strcat(filename, ".ppm");
  
  const int SIZE = 100;
  char *output = malloc(SIZE);
  decrypt(filename, output, SIZE);
  printf("DECRYPTING [%i] BYTES\n---CONTENTS---\n\n%s\n\n---END---\n", SIZE, (char*) output);
}