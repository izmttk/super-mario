#pragma once
#include "BaseObject.h"
class Pipe: public BaseObject
{
    public:
        Pipe():BaseObject(){}
        Pipe(int x, int y, int width = 1, int height = 1):
            BaseObject(x, y, width, height, "pipe") {}
        void setPipe(int x, int y, int width = 1, int height = 1);
        void init() {}
};

