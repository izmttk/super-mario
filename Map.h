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
        //vector<Rocket> rocket_sorted_by_left;
        //vector<Rocket> rocket_sorted_by_right;
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
        bool left_exist_object(BaseObject& t);
        bool right_exist_object(BaseObject& t);
        void check_crash();
};


#endif