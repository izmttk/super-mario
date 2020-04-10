#pragma once
#ifndef _MARIO_H_
#define _MARIO_H_


#include<graphics.h>
#include "BaseObject.h"

#define MARIO_X 0
#define MARIO_Y 343


class Mario: public BaseObject
{
    private:
        int direction;
    public:
        Mario():BaseObject(),direction(RIGHT){}
        void run();
        void jump();
        void still();
        void turn(int d);
        void init();
};


#endif