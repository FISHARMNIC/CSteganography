void decrypt(char* filename, char* buffer, int size)
{
    file_data_t img = fileRead(filename);
    uint8_t* imgb = skipHeader(img.buffer);

    int i = 0;
    while(i < size)
    {
        uint8_t a = *(imgb++);
        uint8_t b = *(imgb++);
        uint8_t c = *(imgb++);

        buffer[i] = 0;

        char bu = 0;
        bu = (a & 0x07) << 3;
        bu = (bu | (b & 0x07)) << 2;
        bu = bu | (c & 0x03);

        buffer[i] = bu;

        i++;
    }
}