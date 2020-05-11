#include "demosaic.h"

typedef struct Pixel
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
}pixel;

void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
    rgb.resize(width*height*3);
    
    unsigned char buffer[height][width];
    
    int index = 0;
    for(int i=0;i<height && index<width*height;++i)
        for(int j=0;j<width && index<width*height;++j)
            buffer[i][j]=bayer[index++];
    
    pixel rgb_buffer[height][width];
    
    for(int i=1;i<height-1;++i)
    {
        for(int j=1;j<width-1;++j)
        {
            //top left green
            if(i%2==0 && j%2==0)
            {
                rgb_buffer[i][j].r = (buffer[i-1][j] + buffer[i+1][j]) / 2;
                rgb_buffer[i][j].g = buffer[i][j];
                rgb_buffer[i][j].b = (buffer[i][j-1] + buffer[i][j+1]) / 2;
            }
            //top right blue
            else if(i%2==0 && j%2!=0)
            {
                rgb_buffer[i][j].r = (buffer[i-1][j-1] + buffer[i-1][j+1] + buffer[i+1][j-1] + buffer[i+1][j+1]) / 4;
                rgb_buffer[i][j].g = (buffer[i-1][j] + buffer[i+1][j] + buffer[i][j-1] + buffer[i][j+1]) / 4;
                rgb_buffer[i][j].b = buffer[i][j];
            }
            //bottom left red
            else if(i%2!=0 && j%2==0)
            {
                rgb_buffer[i][j].r = buffer[i][j];
                rgb_buffer[i][j].g = (buffer[i-1][j] + buffer[i+1][j] + buffer[i][j-1] + buffer[i][j+1]) / 4;
                rgb_buffer[i][j].b = (buffer[i-1][j-1] + buffer[i-1][j+1] + buffer[i+1][j-1] + buffer[i+1][j+1]) / 4;
            }
            //bottom right green
            else
            {
                rgb_buffer[i][j].r = (buffer[i][j-1] + buffer[i][j+1]) / 2;
                rgb_buffer[i][j].g = buffer[i][j];
                rgb_buffer[i][j].b = (buffer[i-1][j]+buffer[i+1][j]) / 2;
            }
        }
    }
    
    rgb_buffer[0][0].r = buffer[1][0];
    rgb_buffer[0][0].g = buffer[0][0];
    rgb_buffer[0][0].b = buffer[0][1];
    
    for(int i=1;i<height-1;++i)
    {
        if(i%2==0)
        {
            rgb_buffer[i][0].r = (buffer[i-1][0] + buffer[i+1][0]) / 2;
            rgb_buffer[i][0].g = buffer[i][0];
            rgb_buffer[i][0].b = buffer[i][1];
            
            if((width-1) % 2 == 0)
            {
                rgb_buffer[i][width-1].r = (buffer[i-1][width-1] + buffer[i+1][width-1]) / 2;
                rgb_buffer[i][width-1].g = buffer[i][width-1];
                rgb_buffer[i][width-1].b = buffer[i][width-2];
            }
            
            else
            {
                rgb_buffer[i][width-1].r = (buffer[i-1][width-2] + buffer[i+1][width-2]) / 2;
                rgb_buffer[i][width-1].g = (buffer[i][width-2] + buffer[i-1][width-1] + buffer[i+1][width-1]) / 3;
                rgb_buffer[i][width-1].b = buffer[i][width-1];
            }
        }
        
        else
        {
            rgb_buffer[i][0].r = buffer[i][0];
            rgb_buffer[i][0].g = (buffer[i-1][0] + buffer[i+1][0] + buffer[i][1]) / 3;
            rgb_buffer[i][0].b = (buffer[i-1][1] + buffer[i+1][1]) / 2;
            
            if((width-1) % 2 == 0)
            {
                rgb_buffer[i][width-1].r = buffer[i][width-1];
                rgb_buffer[i][width-1].g = (buffer[i-1][width-1] + buffer[i+1][width-1] + buffer[i][width-2]) / 3;
                rgb_buffer[i][width-1].b = (buffer[i-1][width-2] + buffer[i+1][width-2]) / 2;
            }
            
            else
            {
                rgb_buffer[i][width-1].r = buffer[i][width-2];
                rgb_buffer[i][width-1].g = buffer[i][width-1];
                rgb_buffer[i][width-1].b = (buffer[i-1][width-1] + buffer[i+1][width-1]) / 2;
            }
        }
    }
    
    
        for(int j=1;j<width-1;++j)
        {
            if(j%2==0)
            {
                rgb_buffer[0][j].r = buffer[1][j];
                rgb_buffer[0][j].g = buffer[0][j];
                rgb_buffer[0][j].b = (buffer[0][j-1] + buffer[0][j+1]) / 2;
                
                if((height-1) % 2 == 0)
                {
                    rgb_buffer[height-1][j].r = buffer[height-2][j];
                    rgb_buffer[height-1][j].g = buffer[height-1][j];
                    rgb_buffer[height-1][j].b = (buffer[height-1][j-1] + buffer[height-1][j+1]) / 2;
                    
                }
                else
                {
                    rgb_buffer[height-1][j].r = buffer[height-1][j];
                    rgb_buffer[height-1][j].g = (buffer[height-1][j-1] + buffer[height-1][j+1] + buffer[height-2][j]) / 3;
                    rgb_buffer[height-1][j].b = (buffer[height-2][j-1] + buffer[height-2][j+1]) / 2;
                }
            }
            else
            {
                rgb_buffer[0][j].r = (buffer[1][j-1] + buffer[1][j+1]) / 2;
                rgb_buffer[0][j].g = (buffer[0][j-1] + buffer[0][j+1] + buffer[1][j]) / 3;
                rgb_buffer[0][j].b = buffer[0][j];
                
                if((height-1) % 2 == 0)
                {
                    rgb_buffer[height-1][j].r = (buffer[height-2][j-1] + buffer[height-2][j+1]) / 2;
                    rgb_buffer[height-1][j].g = (buffer[height-1][j-1] + buffer[height-1][j+1] + buffer[height-2][j]) / 3;
                    rgb_buffer[height-1][j].b = buffer[height-1][j];
                }
                else
                {
                    rgb_buffer[height-1][j].r = (buffer[height-1][j-1] + buffer[height-1][j+1]) / 2;
                    rgb_buffer[height-1][j].g = buffer[height-1][j];
                    rgb_buffer[height-1][j].b = buffer[height-2][j];
                }
            }
        }
            
            if((width-1) % 2 == 0)
            {
                rgb_buffer[0][width-1].r = buffer[1][width-1];
                rgb_buffer[0][width-1].g = buffer[0][width-1];
                rgb_buffer[0][width-1].b = buffer[0][width-2];
                
                if((height-1) % 2 == 0)
                {
                    rgb_buffer[height-1][0].r = buffer[height-2][0];
                    rgb_buffer[height-1][0].g = buffer[height-1][0];
                    rgb_buffer[height-1][0].b = buffer[height-1][1];
                    
                    rgb_buffer[height-1][width-1].r = buffer[height-2][width-1];
                    rgb_buffer[height-1][width-1].g = buffer[height-1][width-1];
                    rgb_buffer[height-1][width-1].b = buffer[height-1][width-2];
                }
                else
                {
                    rgb_buffer[height-1][0].r = buffer[height-1][0];
                    rgb_buffer[height-1][0].g = (buffer[height-2][0] + buffer[height-1][1]) / 2;
                    rgb_buffer[height-1][0].b = buffer[height-2][1];
                    
                    rgb_buffer[height-1][width-1].r = buffer[height-1][width-1];
                    rgb_buffer[height-1][width-1].g = (buffer[height-1][width-2] + buffer[height-2][width-1]) / 2;
                    rgb_buffer[height-1][width-1].b = buffer[height-2][width-2];
                }
            }
            
            else
            {
                rgb_buffer[0][width-1].r = buffer[1][width-2];
                rgb_buffer[0][width-1].g = (buffer[0][width-2] + buffer[1][width-1]) / 2;
                rgb_buffer[0][width-1].b = buffer[0][width-1];
                
                if((height-1) % 2 == 0)
                {
                    rgb_buffer[height-1][0].r = buffer[height-2][0];
                    rgb_buffer[height-1][0].g = buffer[height-1][0];
                    rgb_buffer[height-1][0].b = buffer[height-1][1];
                    
                    rgb_buffer[height-1][width-1].r = buffer[height-2][width-2];
                    rgb_buffer[height-1][width-1].g = (buffer[height-1][width-2] + buffer[height-2][width-1]) / 2;
                    rgb_buffer[height-1][width-1].b = buffer[height-1][width-1];
                }
                else
                {
                    rgb_buffer[height-1][0].r = buffer[height-1][0];
                    rgb_buffer[height-1][0].g = (buffer[height-2][0] + buffer[height-1][1]) / 2;
                    rgb_buffer[height-1][0].b = buffer[height-2][1];
                    
                    rgb_buffer[height-1][width-1].r = buffer[height-1][width-2];
                    rgb_buffer[height-1][width-1].g = buffer[height-1][width-1];
                    rgb_buffer[height-1][width-1].b = buffer[height-2][width-1];
                }
            }
             
    
    index = 0;
    for(int i=0;i<height && index<width*height*3;++i)
    {
        for(int j=0;j<width && index<width*height*3;++j)
        {
            rgb[index++] = rgb_buffer[i][j].r;
            rgb[index++] = rgb_buffer[i][j].g;
            rgb[index++] = rgb_buffer[i][j].b;
        }
    }
}
