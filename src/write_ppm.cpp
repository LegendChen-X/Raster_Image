#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
    assert( (num_channels == 3 || num_channels ==1 ) && ".ppm only supports RGB or grayscale images");
    
    std::ofstream ppm(filename);
    
    if(!ppm) return false;
        
    if(num_channels==3)
    {
        ppm << "P3" << std::endl;
        ppm << width << " " << height << std::endl;
        ppm << "255" << std::endl;
        
        for(int i=0;i<width*height*3;)
        {
            int r = data[i];
            int g = data[i+1];
            int b = data[i+2];
            
            ppm << r << " " << g << " " << b << std::endl;
            
            i = i+3;
        }
    }
    
    if(num_channels==1)
    {
        ppm << "P2" << std::endl;
        ppm << width << " " << height << std::endl;
        ppm << "255" << std::endl;
        
        for(int i=0;i<width*height;++i)
        {
            int g = data[i];
            
            ppm << g << " ";
        }
    }
    
    return true;
}
