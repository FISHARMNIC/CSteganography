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
  file_data_t img = fileRead("images/Cow_female_black_white_640x426.ppm");
  #define DIM 640 * 426
  uint8_t *byteptr = skipHeader(img.buffer);
  color_t col;
  char *data = malloc(DIM);

  printf("secret message: ");
  scanf("%s", data);

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

  fileWrite("output.ppm", img);

}