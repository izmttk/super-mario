#include<conio.h>
#include<ctime>
#include "Mario.h"
#include "Map.h"
#include "Player.h"

Map map;
Mario mario;
//开始界面
void start() {

}

//更新实时数据
void update() {
    if(GetAsyncKeyState(VK_SPACE))
        mario.jump();
    else if(GetAsyncKeyState(VK_LEFT))
        mario.run(LEFT);
    else if(GetAsyncKeyState(VK_RIGHT))
        mario.run(RIGHT);
    else mario.still();

    mario.update();
}

//刷新画面
void reflush() {
    cleardevice();
    map.show();
    mario.show();
    FlushBatchDraw();
    //_getch();
}


int main()
{
    initgraph(WINDOWS_WIDTH, WINDOWS_HEIGHT, SHOWCONSOLE);

    map.loadResource();
    mario.loadResource();

    BeginBatchDraw();
    while(true)
    {
        start();
        update();
        reflush();
    }
    EndBatchDraw();
    closegraph();
    return 0;
}