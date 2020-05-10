#include "hue_shift.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"
#include <stdio.h>

typedef struct Pixel
{
    double r;
    double g;
    double b;
}pixel;

typedef struct HSV
{
    double h;
    double s;
    double v;
}hsv;

void hue_shift(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double shift,
  std::vector<unsigned char> & shifted)
{
    shifted.resize(rgb.size());
    
    pixel rgb_buff[height][width];
    hsv hsv_buff[height][width];
    
    int index = 0;
    for(int i=0;i<height && index<height*width*3;++i)
    {
        for(int j=0;j<width && index<height*width*3;++j)
        {
            rgb_buff[i][j].r = (double)rgb[index++] / 255;
            rgb_buff[i][j].g = (double)rgb[index++] / 255;
            rgb_buff[i][j].b = (double)rgb[index++] / 255;
        }
    }

    for(int i=0;i<height;++i)
    {
        for(int j=0;j<width;++j)
        {
            rgb_to_hsv(rgb_buff[i][j].r,rgb_buff[i][j].g,rgb_buff[i][j].b,hsv_buff[i][j].h,hsv_buff[i][j].s,hsv_buff[i][j].v);
            hsv_buff[i][j].h = hsv_buff[i][j].h + shift;
            if(hsv_buff[i][j].h>=360) hsv_buff[i][j].h = hsv_buff[i][j].h - 360;
            if(hsv_buff[i][j].h<0) hsv_buff[i][j].h = hsv_buff[i][j].h + 360;
            hsv_to_rgb(hsv_buff[i][j].h,hsv_buff[i][j].s,hsv_buff[i][j].v,rgb_buff[i][j].r,rgb_buff[i][j].g,rgb_buff[i][j].b);
        }
    }
    
    index = 0;
    for(int i=0;i<height && index<height*width*3;++i)
    {
        for(int j=0;j<width && index<height*width*3;++j)
        {
            shifted[index++] = (unsigned char)(rgb_buff[i][j].r*255);
            shifted[index++] = (unsigned char)(rgb_buff[i][j].g*255);
            shifted[index++] = (unsigned char)(rgb_buff[i][j].b*255);
        }
    }
    
    
}
