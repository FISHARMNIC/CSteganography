#include <math.h>

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} color_t;

/*
load each color into the array
*/

color_t encrypt(color_t col, uint8_t data)
{

    uint8_t c1 = col.r & 0b11111000;
    uint8_t c2 = col.g & 0b11111000;
    uint8_t c3 = col.b & 0b11111100;

    if (data || !encript_nulls)
    {
        col.r = c1 | (data >> 5);
        col.g = ((data >> 2) & 0x07) | c2;
        col.b = (data & 0x03) | c3;
    }

    return col;
}