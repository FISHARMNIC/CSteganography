#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

int encript_nulls = 0;

#include "openFile.c"
#include "writeFile.c"
#include "encrypt.c"

#define DIM 640 * 426

int main()
{
  printf("\
-----C-Steganography ENCRYPTER-----\n\
For all file names do not put the extension\n\
  For example, for 'cow.ppm' type 'cow'\n\
All input images must be [ppm 6]\n\
Encrypting NULLS\n\
  pro: Less image alteration\n\
  con: create stange characters after the message\n\
-------------------------\n");
  char *filename = malloc(100);
  printf("Input image name: ");
  scanf("%s", filename);
  getchar();
  strcat(filename, ".ppm");
  file_data_t img = fileRead(filename);
  free(filename);

  uint8_t *byteptr = skipHeader(img.buffer);
  color_t col;
  char *data = malloc(DIM);

  printf("secret message: ");
  scanf("%[^\n]%*c", data);

  printf("Encrypt NULLS (0 or 1): ");
  scanf("%i", &encript_nulls);
  // flood test
  //  char * dd = data;
  //  for(int i = 0; i < DIM; i++)
  //  {
  //    *(dd++) = i % 255;
  //  }

  for (int i = 0; i < (DIM); i++)
  {
    col.r = *byteptr;
    col.g = *(byteptr + 1);
    col.b = *(byteptr + 2);
    col = encrypt(col, data[i]);
    *(byteptr++) = col.r;
    *(byteptr++) = col.g;
    *(byteptr++) = col.b;
  }

  printf("Name of output file: ");
  filename = malloc(100);
  scanf("%s", filename);
  strcat(filename, ".ppm");
  fileWrite(filename, img);
}