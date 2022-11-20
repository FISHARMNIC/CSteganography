#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

uint8_t *skipHeader(uint8_t *ptr);
void print_byte_as_bits(char val)
{
  for (int i = 7; 0 <= i; i--)
  {
    printf("%c", (val & (1 << i)) ? '1' : '0');
  }
  printf("\n");
}
#define SHOW(n) print_byte_as_bits(n)

#include "openFile.c"
#include "writeFile.c"
#include "encrypt.c"
#include "decrypt.c"

uint8_t *skipHeader(uint8_t *ptr)
{
  // uint8_t * copy = ptr;
  while (*ptr != '2' && *(ptr + 1) != '5' && *(ptr + 2) != '5')
    ptr++;
  ptr += 7;
  // printf("skip %u\n", (uint32_t)ptr - (uint32_t)copy);
  return ptr;
  // P6 WIDTH HEIGHT MAXCOLOR <- extra space at end
}

int main()
{
  printf("\
-----C-Steganography ENCRYPTER-----\n\
For all file names do not put the extension\n\
  For example, for 'cow.ppm' type 'cow'\n\
All input images must be [ppm 6]\n\
-------------------------\n");
  char * filename = malloc(100);
  printf("Input image name: ");
  scanf("%s", filename);
  getchar();
  strcat(filename, ".ppm");
  file_data_t img = fileRead(filename);
  free(filename);

  #define DIM 640 * 426
  uint8_t *byteptr = skipHeader(img.buffer);
  color_t col;
  char *data = malloc(DIM);

  printf("secret message: ");
  scanf("%[^\n]%*c", data);

  for (int i = 0; i < (DIM); i++)
  {
    col.colors[0] = *byteptr;
    col.colors[1] = *(byteptr + 1);
    col.colors[2] = *(byteptr + 2);
    col = encrypt(col, data[i]);
    // printf("%u %u %u\n", col.colors[0], col.colors[1], col.colors[2]);
    *(byteptr++) = col.colors[0];
    *(byteptr++) = col.colors[1];
    *(byteptr++) = col.colors[2];
  }

  printf("Name of output file: ");
  filename = malloc(100);
  scanf("%s", filename);
  strcat(filename, ".ppm");
  fileWrite(filename, img);
}