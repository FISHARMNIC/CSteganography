#include <assert.h>

typedef struct
{
    int length;
    uint8_t* buffer;
} file_data_t;

file_data_t fileRead(const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    fseek(fp, 0, SEEK_END);
    int length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    uint8_t *buffer = (uint8_t *)malloc(length);
    assert(buffer != 0);
    fread(buffer, 1, length, fp);
    fclose(fp);
    return (file_data_t){
        .length = length,
        .buffer = buffer,
    };
}