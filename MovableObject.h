#pragma once
#include "Global.h"

//时间比例，RATE=1000 ms : 数据刷新间隔，用于每次数据刷新的换算
#define RATE 100.0

//重力加速度
#define G 25

//MovableObject：所有可移动“活物”的基类
class MovableObject
{
    protected:
        double x;
        double y;
        double vx;
        double vy;
        double ax;
        double ay;
        bool is_running;
        bool is_jumping;
        int direction;
    public:
        MovableObject(int, int, bool, bool, int);
        int getX();
        int getY();
        void setX(double);
        void setY(double);
        void run(int, double);
        void jump();
        void still();
        void update();
};


inline MovableObject::MovableObject(int dx, int dy, bool run = 0, bool jump = 0, int drt = RIGHT):
    x(dx), y(dy), vx(0), vy(0), ax(0),ay(G/RATE),is_running(run), is_jumping(jump), direction(drt) {};

//实数四舍五入后的整数X
inline int MovableObject::getX()
{
    return round(x);
}

//实数四舍五入后的整数Y
inline int MovableObject::getY()
{
    return round(y);
}

//设置X
inline void MovableObject::setX(double dx)
{
    x = dx;
}

//设置Y
inline void MovableObject::setY(double dy)
{
    y = dy;
}

//进入行走状态，横向移动，drt：方向，speed：速度（单位px/s）
inline void MovableObject::run(int drt, double speed = 250)
{
    if(drt == LEFT) {
        vx=0-speed/RATE;
    }
    if(drt == RIGHT) {
        vx=speed/RATE;
    }
    direction = drt;

    if(is_jumping)
        is_running = 0;
    else
        is_running = 1;
}

//进入跳跃状态，设置向上的初速度
inline void MovableObject::jump()
{
    vy = 0-500.0/RATE;
    is_jumping = 1;
}

//进入静止状态
inline void MovableObject::still()
{
    vx = 0;
    is_running = is_jumping = 0;
}

//更新实时数据
inline void MovableObject::update()
{
    static clock_t last = clock();//定时器
    static clock_t now = clock();//定时器
    //可以使用C++11里面的chrono替代，有空研究
    //做定时器的目的是精确控制速度和位移
    if((now=clock()) - last >= 10) {
        last = now; 
        x += vx;
        y += vy;
        vx += ax;
        vy += ay;
        //其实有公式可以更精确计算
        //但是用微分精确度也可以，而且简单
    }
}
