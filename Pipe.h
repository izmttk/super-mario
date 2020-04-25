#pragma once
#include "BaseObject.h"
class Pipe: public BaseObject
{
    public:
        Pipe():BaseObject(){}
        Pipe(int x, int y, int width, int height);
        void setPipe(int x, int y, int width, int height);
};

