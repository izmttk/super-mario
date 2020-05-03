#pragma once
#ifndef _MARIO_H_
#define _MARIO_H_

#define NORMAL_RUN_SPEED 0.3
#define NORMAL_JUMP_SPEED -1.1

#include<graphics.h>
#include "BaseObject.h"

#define MARIO_X unit_length*1
#define MARIO_Y unit_length*10


class Mario: public BaseObject
{
    private:
        int direction;
    public:
        Mario():BaseObject(MARIO_X, MARIO_Y),direction(RIGHT){}
        void run(double speed = NORMAL_RUN_SPEED);
        void jump(double speed = NORMAL_JUMP_SPEED);
        void still();
        void turn(int d = RIGHT);
        void init();
        void kill();
};


#endif