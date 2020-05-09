#include "rgba_to_rgb.h"

void rgba_to_rgb(
  const std::vector<unsigned char> & rgba,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(height*width*3);
    int j = 0;
    for(int i=0;i<width*height*4 && j<height*width*3;++i)
        if(i%4!=3)
            rgb[j++]=rgba[i];
}
