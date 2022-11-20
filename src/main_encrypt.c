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
  // #region DEBUG
/*
    color_t coll;
    coll.colors[0] = 0xAA;
    coll.colors[1] = 0x55;
    coll.colors[2] = 0x8B;

    char data = 'h';

    SHOW(coll.colors[0]);
    SHOW(coll.colors[1]);
    SHOW(coll.colors[2]);

    coll = encrypt(coll, data);

    printf("ENCRYPTED\n");

    SHOW(coll.colors[0]);
    SHOW(coll.colors[1]);
    SHOW(coll.colors[2]);

    printf("CHAR\n");
    SHOW(data);

    printf("SPLIT\n");

    SHOW(data >> 5);
    SHOW((data >> 2) & 0x07);
    SHOW(data & 0x03);

    // decrypt
    uint8_t a = coll.colors[0];
    uint8_t b = coll.colors[1];
    uint8_t c = coll.colors[2];

    printf("----DEC----\n---COLORS---\n");
    SHOW(a);
    SHOW(b);
    SHOW(c);

    printf("---\n");
    SHOW(a & 0x07);
    SHOW(b & 0x07);
    SHOW(c & 0x03);

    char bu = 0;

    bu = (a & 0x07) << 3;
    bu = (bu | (b & 0x07)) << 2;
    bu = bu | (c & 0x03);

    printf("----\n");
    SHOW(bu);
    printf("%c\n", bu);

    return 0;
*/
  // #endregion
  //---------------------- final code

  file_data_t img = fileRead("images/sample_640_426.ppm");
  #define DIM 640 * 426
  uint8_t *byteptr = skipHeader(img.buffer);
  color_t col;
  char *data = malloc(DIM);

  strcpy(data, "rio is the best");

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