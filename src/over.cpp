#include "over.h"
typedef struct Pixel
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    double alpha;
}pixel;

void over(
  const std::vector<unsigned char> & A,
  const std::vector<unsigned char> & B,
  const int & width,
  const int & height,
  std::vector<unsigned char> & C)
{
    C.resize(A.size());
    
    pixel A_buff[height][width];
    pixel B_buff[height][width];
    pixel C_buff[height][width];
    
    int index = 0;
    for(int i=0;i<height && index<height*width*4;++i)
    {
        for(int j=0;j<width && index<height*width*4;++j)
        {
            A_buff[i][j].r = A[index];
            B_buff[i][j].r = B[index++];
            A_buff[i][j].g = A[index];
            B_buff[i][j].g = B[index++];
            A_buff[i][j].b = A[index];
            B_buff[i][j].b = B[index++];
            A_buff[i][j].alpha = (double)A[index] / 255;
            B_buff[i][j].alpha = (double)B[index++] / 255;
        }
    }
    
    for(int i=0;i<height;++i)
    {
        for(int j=0;j<width;++j)
        {
            C_buff[i][j].r = A_buff[i][j].r * A_buff[i][j].alpha + B_buff[i][j].r * (1 - A_buff[i][j].alpha);
            C_buff[i][j].g = A_buff[i][j].g * A_buff[i][j].alpha + B_buff[i][j].g * (1 - A_buff[i][j].alpha);
            C_buff[i][j].b = A_buff[i][j].b * A_buff[i][j].alpha + B_buff[i][j].b * (1 - A_buff[i][j].alpha);
            C_buff[i][j].alpha = A_buff[i][j].alpha * A_buff[i][j].alpha + B_buff[i][j].alpha * (1 - A_buff[i][j].alpha);
        }
    }
    
    index = 0;
    for(int i=0;i<height && index<height*width*4;++i)
    {
        for(int j=0;j<width && index<height*width*4;++j)
        {
            C[index++] = C_buff[i][j].r;
            C[index++] = C_buff[i][j].g;
            C[index++] = C_buff[i][j].b;
            C[index++] = C_buff[i][j].alpha;
        }
    }
}
