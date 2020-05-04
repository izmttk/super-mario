#pragma once
#ifndef _MAP_H_
#define _MAP_H_



#include <graphics.h>
#include "Global.h"
#include "Rocket.h"
#include "Pipe.h"
#include "Enemy.h"

class Map
{
    private:
        IMAGE background;
        vector<BaseObject*> object;
        vector<Enemy*> enemy;
        BaseObject*  hero;
        int _width;
        int _height;
    public:
        Map():background(NULL), object({}), enemy({}), hero(NULL),_width(0),_height(0){};
        void init(BaseObject* h);
        void show(Vector offset);
        int width();
        int height();
        void update(double time);
        bool left_exist(BaseObject& t);
        bool right_exist(BaseObject& t);
        string collision(BaseObject& a, BaseObject& b, bool left_exist, bool right_exist);
        void check_collision();
        void add_rocket(int x, int y, int width = 1, int height = 1, string type = "rock0");
        void add_pipe(int x, int y, int width = 1, int height = 1);
        void add_enemy(int x, int y, int range_left, int range_right, double v = 0.2);
};


#endif