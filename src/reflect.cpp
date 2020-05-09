#include "reflect.h"

typedef struct Pixel
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
}pixel;

void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected)
{
    reflected.resize(width*height*num_channels);
    
    if(num_channels==3)
    {
        pixel buffer[height][width];
        
        int index = 0;
        for(int i=0;i<height && index<width*height*num_channels;++i)
        {
            for(int j=0;j<width && index<width*height*num_channels;++j)
            {
                buffer[i][j].r=input[index++];
                buffer[i][j].g=input[index++];
                buffer[i][j].b=input[index++];
            }
        }
        
        for(int i=0;i<height;++i)
        {
            for(int j=0;j<width/2;++j)
            {
                pixel tmp = buffer[i][j];
                buffer[i][j] = buffer[i][width-j];
                buffer[i][width-j] = tmp;
            }
        }
        
        index = 0;
        for(int i=0;i<height && index<width*height*num_channels;++i)
        {
            for(int j=0;j<width && index<width*height*num_channels;++j)
            {
                reflected[index++]=buffer[i][j].r;
                reflected[index++]=buffer[i][j].g;
                reflected[index++]=buffer[i][j].b;
            }
        }
    }
    
}
