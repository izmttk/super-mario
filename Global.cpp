#include "Global.h"
#include <utility>
void rotateFlip(IMAGE* img)
{
    DWORD* img_pMem = GetImageBuffer(img);

    for(int y = 0; y < img->getheight(); y++)
    {
        for(int x = 0; x< int(img->getwidth() / 2 + 0.5); x++)
        {
            int num1 = y * img->getwidth() + x;
            int num2 = (y + 1) * img->getwidth() - x - 1;
            std::swap(img_pMem[num1], img_pMem[num2]);
        }
    }
}
