void fileWrite(const char *filename, file_data_t img)
{
  FILE *fp = fopen(filename, "wb");
  fwrite(img.buffer, img.length, 1, fp);
  fclose(fp);
}