#include <math.h>

typedef union
{
    uint8_t colors[3];
    uint32_t color32;
} color_t;

/*
load each color into the array
read the number as a whole, and get each digit
*/

color_t encrypt(color_t col, uint8_t data)
{
/*

0xAA;
0x55;
0x8B;

*/
    uint8_t c1 = col.colors[0] & 0b11111000;
    uint8_t c2 = col.colors[1] & 0b11111000;
    uint8_t c3 = col.colors[2] & 0b11111100;
    
    //printf("MASKED: %0x %0x %0x || DECIMAL %i %i %i\n", c1, c2, c3, c1, c2, c3);
    color_t out;

    out.colors[0] = c1 | (data >> 5);
    out.colors[1] = ((data >> 2) & 0x07) | c2;

    // printf("DBG: ");
    // SHOW(data);
    // SHOW(data & 0x03);
    // printf("END DBG\n");
    out.colors[2] = (data & 0x03) | c3;


    return out;

    //col.colors[1] = c2 | (data >> 2 && 0xb00000111);
}