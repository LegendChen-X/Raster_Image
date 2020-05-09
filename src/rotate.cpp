#include "rotate.h"

typedef struct Pixel
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
}pixel;

void rotate(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & rotated)
{
    rotated.resize(height*width*num_channels);
    
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
        
        pixel r_buff[width][height];
        for(int i=0;i<height;++i)
            for(int j=0;j<width;++j)
                r_buff[width-j-1][i]=buffer[i][j];
        
        index = 0;
        for(int i=0;i<width && index<width*height*num_channels;++i)
        {
            for(int j=0;j<height && index<width*height*num_channels;++j)
            {
                rotated[index++]=r_buff[i][j].r;
                rotated[index++]=r_buff[i][j].g;
                rotated[index++]=r_buff[i][j].b;
            }
        }
        
    }
    
    if(num_channels==1)
    {
        unsigned char buffer[height][width];
        
        int index = 0;
        
        for(int i=0;i<height && index<width*height*num_channels;++i)
            for(int j=0;j<width && index<width*height*num_channels;++j)
                buffer[i][j]=input[index++];
        
        unsigned char r_buff[width][height];
        for(int i=0;i<height;++i)
            for(int j=0;j<width;++j)
                r_buff[width-j-1][i]=buffer[i][j];
        
        index = 0;
        for(int i=0;i<width && index<width*height*num_channels;++i)
            for(int j=0;j<height && index<width*height*num_channels;++j)
                rotated[index++]=r_buff[i][j];
    }
}
