#pragma once
#include "BaseObject.h"
class Enemy: public BaseObject
{
    private:
        double range_left, range_right;
        time_point<steady_clock> kill_tick;
    public:
        Enemy():BaseObject(unit_length * 4, unit_length * 11),range_left(0),range_right(0){}
        Enemy(const double x, const double y,const double range_left,const double range_right):
            BaseObject(x,y),range_left(range_left),range_right(range_right){}
        void init();
        void kill();
        void move_range(double a, double b);
        double move_range_left();
        double move_range_right();
        bool is_removed();

};

