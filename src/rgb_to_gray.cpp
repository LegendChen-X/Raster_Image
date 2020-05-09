#include "rgb_to_gray.h"

typedef struct Pixel
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
}pixel;

void rgb_to_gray(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  std::vector<unsigned char> & gray)
{
    gray.resize(height*width);
    
    pixel buffer[height][width];
    
    int index = 0;
    for(int i=0;i<height && index<width*height*3;++i)
    {
        for(int j=0;j<width && index<width*height*3;++j)
        {
            buffer[i][j].r=rgb[index++];
            buffer[i][j].g=rgb[index++];
            buffer[i][j].b=rgb[index++];
        }
    }
    
    pixel g_buff[width][height];
    
    index=0;
    for(int i=0;i<height;++i)
        for(int j=0;j<width;++j)
            gray[index++] = 0.2126*buffer[i][j].r + 0.7152*buffer[i][j].g + 0.0722*buffer[i][j].b;
}


