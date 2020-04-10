#pragma once
#ifndef _ROCKET_H_
#define _ROCKET_H_

#include "BaseObject.h"
class Rocket : public BaseObject
{
    public:
        Rocket():BaseObject(){}
        Rocket(int x, int y, int width, int height);
        void setRocket(int x,int y,int width,int height);
};

#endif