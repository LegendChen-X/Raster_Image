#include "desaturate.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

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
void desaturate(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double factor,
  std::vector<unsigned char> & desaturated)
{
    desaturated.resize(rgb.size());
    
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
            hsv_buff[i][j].s = hsv_buff[i][j].s * (1 - factor);
            hsv_to_rgb(hsv_buff[i][j].h,hsv_buff[i][j].s,hsv_buff[i][j].v,rgb_buff[i][j].r,rgb_buff[i][j].g,rgb_buff[i][j].b);
        }
    }
    
    index = 0;
    for(int i=0;i<height && index<height*width*3;++i)
    {
        for(int j=0;j<width && index<height*width*3;++j)
        {
            desaturated[index++] = (unsigned char)(rgb_buff[i][j].r*255);
            desaturated[index++] = (unsigned char)(rgb_buff[i][j].g*255);
            desaturated[index++] = (unsigned char)(rgb_buff[i][j].b*255);
        }
    }
    
}
