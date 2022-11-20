#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "openFile.c"
#include "decrypt.c"

int main()
{
  printf("\
-----C-Steganography DECRYPTER-----\n\
For all file names do not put the extension\n\
  For example, for 'cow.ppm' type 'cow'\n\
-------------------------\n");
  char *filename = malloc(100);
  printf("file name: ");
  scanf("%s", filename);
  strcat(filename, ".ppm");
  printf("maxiumim length: ");

  int size;
  scanf("%i", &size);
  char *output = malloc(size);
  decrypt(filename, output, size);
  printf("DECRYPTING [%i] BYTES\n---CONTENTS---\n\n%s\n\n---END---\n", size, (char *)output);
}