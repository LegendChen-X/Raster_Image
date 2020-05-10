#include "rgb_to_hsv.h"
#include "stdio.h"
double max_function(double r, double g, double b)
{
    double comparator = r > g ? r : g;
    return comparator > b ? comparator : b;
}
double min_function(double r, double g, double b)
{
    double comparator = r < g ? r : g;
    return comparator < b ? comparator : b;
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
    
    v = max_function(r,g,b);
    double c_min = min_function(r,g,b);
    double delta = v - c_min;
    
    if(delta==0) h = 0;
    else if(v==r) h = 60 * ((g - b) / delta);
    else if(v==g) h = 60 * ((b - r) / delta + 2);
    else if(v==b) h = 60 * ((r - g) / delta + 4);
    
    if(v==0) s = 0;
    else s = delta / v;
    
}
