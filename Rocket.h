#pragma once
#ifndef _ROCKET_H_
#define _ROCKET_H_

#include "BaseObject.h"
class Rocket : public BaseObject
{
    private:
        string _type;
    public:
        Rocket():BaseObject(), _type("rock0"){}
        Rocket(int x, int y, int width = 1, int height = 1, string type = "rock0");
        void setRocket(int x, int y, int width = 1, int height = 1, string type="rock0");
        string type();
        void init();
};

#endif