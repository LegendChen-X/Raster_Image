#include "rgb_to_hsv.h"

double max_function(double r, double g, double b)
{
    double comparator = r ? g : r > g;
    return comparator ? b : comparator > b;
}

double min_function(double r, double g, double b)
{
    double comparator = r ? g : r < g;
    return comparator ? b : comparator < b;
}

void rgb_to_hsv(
  const double r,
  const double g,
  const double b,
  double & h,
  double & s,
  double & v)
{
    h = 0;
    s = 0;
    v = 0;
    
    double r_c = r / 255;
    double g_c = g / 255;
    double b_c = b / 255;
    
    v = max_function(r_c,g_c,b_c);
    c_min = min_function(r_c,g_c,b_c);
    double delta = v - c_min;
    
    if(delta==0) h = 0;
    else(v == r_c) h = 60 * ((g_c - b_c) / delta);
    else if(v == g_c) h = 60 * ((b_c - r_c) / delta + 2);
    else if(v == b_c) h = 60 * ((b_c - r_c) / delta + 4);
    
    if(v == 0) s = 0;
    else s = delta / v;
    
}
