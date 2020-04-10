#pragma once
#ifndef _MAP_H_
#define _MAP_H_


#include <graphics.h>
#include "Global.h"
#include "Rocket.h"

class Map
{
    private:
        IMAGE background;
        vector<Rocket> rocket;
        BaseObject*  hero;
    public:
        Map():background(NULL), rocket({}),hero(NULL){};
        void init(BaseObject* h);
        void show();
        void update();
        void check_crash();
};


#endif