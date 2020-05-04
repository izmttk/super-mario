#pragma once
#ifndef _ROCKET_H_
#define _ROCKET_H_

#include "BaseObject.h"
class Rocket : public BaseObject
{
    public:
        Rocket():BaseObject(){}
        Rocket(int x, int y, int width = 1, int height = 1, string type = "rock0"):
            BaseObject(x, y, width, height, type){}
        void setRocket(int x, int y, int width = 1, int height = 1, string type="rock0");
        void init();
};

#endif