#include "hsv_to_rgb.h"
#include <stdlib.h>
#include <math.h>

void hsv_to_rgb(
  const double h,
  const double s,
  const double v,
  double & r,
  double & g,
  double & b)
{
    r = 0;
    g = 0;
    b = 0;
    
    double c = v * s;
    double h_c = h / 60;
    double x = c * (1 - abs(fmod(h_c,2) - 1));
    double m = v - c;
    
    double r_c;
    double g_c;
    double b_c;
    
    if(0<=h_c && h_c<=1)
    {
        r_c = c;
        g_c = x;
        b_c = 0;
    }
    else if(1<h_c && h_c<=2)
    {
        r_c = x;
        g_c = c;
        b_c = 0;
    }
    else if(2<h_c && h_c<=3)
    {
        r_c = 0;
        g_c = c;
        b_c = x;
    }
    else if(3<h_c && h_c<=4)
    {
        r_c = 0;
        g_c = x;
        b_c = c;
    }
    else if(4<h_c && h_c<=5)
    {
        r_c = x;
        g_c = 0;
        b_c = c;
    }
    else
    {
        r_c = c;
        g_c = 0;
        b_c = x;
    }
    
    r = r_c + m;
    g = g_c + m;
    b = b_c + m;
}
