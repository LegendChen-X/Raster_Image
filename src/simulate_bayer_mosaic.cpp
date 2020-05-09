#include "simulate_bayer_mosaic.h"

typedef struct Pixel
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
}pixel;

void simulate_bayer_mosaic(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<unsigned char> & bayer)
{
    bayer.resize(width*height);
    
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
    
    index = 0;
    for(int i=0;i<height && index<width*height;++i)
    {
        for(int j=0;j<width && index<width*height;++j)
        {
            if(i%2==0 && j%2!=0)
                bayer[index++] = buffer[i][j].b;
            else if(i%2!=0 && j%2==0)
                bayer[index++] = buffer[i][j].r;
            else
                bayer[index++] = buffer[i][j].g;
        }
    }
}
