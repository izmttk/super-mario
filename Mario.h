#pragma once

#include<graphics.h>
#include "Global.h"
#include "MovableObject.h"

#define MARIO_X 0
#define MARIO_Y 343

class Mario_figure
{
    private:
        IMAGE running_figure[10];
        IMAGE running_figure_mask[10];
        IMAGE still_figure;
        IMAGE still_figure_mask;
        IMAGE jump_figure;
        IMAGE jump_figure_mask;
        int direction;
        void LoadImages(int, LPCTSTR, LPCTSTR);
        void changeDirection();
    public:   
        Mario_figure();
        void loadResource();
        void show(int, int, int, int);
};

class Mario: public MovableObject
{
    private:
        Mario_figure figure;
    public:
        Mario();
        void loadResource();
        void show();
};

inline void Mario_figure::LoadImages(int figure_num, LPCTSTR f_src, LPCTSTR fm_src)
{
    IMAGE origin, organ_mask;
    loadimage(&origin, f_src);
    loadimage(&organ_mask, fm_src);
    int width = origin.getwidth()/figure_num;
    int height = origin.getheight();

    SetWorkingImage(&origin);
    getimage(&still_figure, 0, 0, width, height);
    for(int i = 0; i<3; i++)
        getimage(&running_figure[i], width+width*i, 0, width, height);
    getimage(&jump_figure, width*4, 0, width, height);

    SetWorkingImage(&organ_mask);
    getimage(&still_figure_mask, 0, 0, width, height);
    for(int i = 0; i<3; i++)
        getimage(&running_figure_mask[i], width+width*i, 0, width, height);
    getimage(&jump_figure_mask, width*4, 0, width, height);

    SetWorkingImage(NULL);
}

inline void Mario_figure::changeDirection()
{
    rotateFlip(&still_figure);
    rotateFlip(&still_figure_mask);
    rotateFlip(&jump_figure);
    rotateFlip(&jump_figure_mask);
    for(int i = 0; i < 3; i++)
        rotateFlip(&running_figure[i]),
        rotateFlip(&running_figure_mask[i]);
}


inline Mario_figure::Mario_figure():direction(RIGHT){}

inline void Mario_figure::loadResource()
{
    LoadImages(5, _T("assert\\images\\mario.png"), _T("assert\\images\\mario_mask.png"));
}

inline void Mario_figure::show(int status, int drt, int x, int y)
{
    static clock_t last = clock();//定时器
    static int running_cnt = 0;//动作变化计数
    if(direction != drt) {
        changeDirection();
        direction = drt;
    }
    switch(status)
    {
        case RUNNING:
            putimage(x, y, &running_figure_mask[running_cnt], NOTSRCERASE);
            putimage(x, y,&running_figure[running_cnt], SRCINVERT);
            if((clock() - last) >= 100) {//定时器，动作变化间隔100ms
                last = clock();
                running_cnt = (running_cnt + 1) % 3;
            }
            break;
        case STILL:
            putimage(x, y, &still_figure_mask, NOTSRCERASE);
            putimage(x, y, &still_figure, SRCINVERT);
            running_cnt = 0;
            break;
        case JUMPPING:
            putimage(x, y, &jump_figure_mask, NOTSRCERASE);
            putimage(x, y, &jump_figure, SRCINVERT);
            running_cnt = 0;
            break;
    }
}



inline Mario::Mario():MovableObject(MARIO_X,MARIO_Y){}

inline void Mario::loadResource()
{
    figure.loadResource();
}

inline void Mario::show()
{
    if(is_running)figure.show(RUNNING, direction, getX(), getY());
    else if(is_jumping)figure.show(JUMPPING, direction, getX(), getY());
    else
        figure.show(STILL, direction, getX(), getY());
}