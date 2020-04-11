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
        int _width;
        int _height;
    public:
        Map():background(NULL), rocket({}),hero(NULL),_width(0),_height(0){};
        void init(BaseObject* h);
        void show(Vector offset);
        int width();
        int height();
        void update();
        void check_crash();
};


#endif