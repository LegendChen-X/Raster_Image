#include "rgb_to_hsv.h"

double max_function(double r, double g, double b)
{
    double comparator = r ? g : r > g;
    return comparator : b : comparator > b;
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
    
    C_max = max_function(r_c,g_c,b_c);
    
}
