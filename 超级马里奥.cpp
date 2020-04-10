#include<conio.h>
#include<ctime>
#include "Mario.h"
#include "Map.h"
#include "Controller.h"

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
        mario.turn(LEFT), mario.run();
    else if(GetAsyncKeyState(VK_RIGHT))
        mario.turn(RIGHT), mario.run();
    else mario.still();

}

//刷新画面
void reflush(int x) {
    mario.update(x);
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
    mario.init();

    BeginBatchDraw();

    const int TICKS_PER_SECOND = 25;
    const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
    const int MAX_FRAMESKIP = 5;

    DWORD next_game_tick = GetTickCount();
    int loops;
    float interpolation;

    bool game_is_running = true;
    while(game_is_running) {

        loops = 0;
        while(GetTickCount() > next_game_tick&& loops < MAX_FRAMESKIP) {
            update();
            next_game_tick += SKIP_TICKS;
            loops++;
        }

        interpolation = float(GetTickCount() + SKIP_TICKS - next_game_tick)
            / float(SKIP_TICKS);
        reflush(interpolation);
    }

    EndBatchDraw();
    closegraph();
}