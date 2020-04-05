#pragma once

#define WINDOWS_WIDTH 640
#define WINDOWS_HEIGHT 480

#define DEBUG
#ifdef DEBUG
#include<iostream>
#include<cstdio>
using namespace std;
#endif

#define RUNNING 0
#define STILL 1
#define JUMPPING 2

#define RIGHT 0
#define LEFT 1


#include<utility>
void rotateFlip(IMAGE* img)
{
    DWORD* img_pMem = GetImageBuffer(img);

    for(int y = 0; y< img->getheight(); y++)
    {
        for(int x = 0; x< int(img->getwidth()/2+0.5); x++)
        {
            int num1 = y*img->getwidth()+x;
            int num2 = (y+1)*img->getwidth()-x-1;
            std::swap(img_pMem[num1], img_pMem[num2]);
        }
    }
}
