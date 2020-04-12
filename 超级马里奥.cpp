#include<conio.h>
#include<ctime>
#include <chrono>   
#include "Mario.h"
#include "Map.h"
//#include "Player.h"

Mario mario;
Map map;
//开始界面
void start() {

}


//更新数据
void update() {
    if(GetAsyncKeyState(VK_SPACE) || GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT)) {
        if(GetAsyncKeyState(VK_SPACE))
            mario.jump();
        if(GetAsyncKeyState(VK_LEFT))
            mario.turn(LEFT), mario.run();
        if(GetAsyncKeyState(VK_RIGHT))
            mario.turn(RIGHT), mario.run();
    }
    else mario.still();
}

//刷新画面
void reflush(double time) {
    mario.update(time);
    map.update();
    cleardevice();

    //offset:地图和人物相对视窗位移，用于使视窗跟随人物移动
    //开头处人物未超过视窗宽度1/2，不发生位移
    Vector offset(0, 0);
    if(mario.position.x() + mario.width() / 2 >= WINDOWS_WIDTH / 2 && 
       mario.position.x() + mario.width() / 2 <= map.width() - WINDOWS_WIDTH / 2) {
        //始终保持人物居中
        offset.x(-(mario.position.x() + mario.width() / 2 - WINDOWS_WIDTH / 2));
    }
    else if(mario.position.x() + mario.width() / 2 > map.width() - WINDOWS_WIDTH / 2) {
        //人物距离结束处不足窗口1/2，停止位移
        offset.x(-(map.width() - WINDOWS_WIDTH));
    }
    map.show(offset);
    mario.show(offset);
    FlushBatchDraw();
}


int main()
{
    initgraph(WINDOWS_WIDTH, WINDOWS_HEIGHT, SHOWCONSOLE);

    mario.init();
    map.init(&mario);

    BeginBatchDraw();

    const int TICKS_PER_SECOND = 60;
    const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
    const int MAX_FRAMESKIP = 5;

    using namespace std::chrono;

    auto next_game_tick = steady_clock::now();
    int loops;
    double interpolation;
    bool game_is_running = true;
    while(game_is_running) {

        loops = 0;
        while(steady_clock::now() > next_game_tick&& loops < MAX_FRAMESKIP) {
            update();
            next_game_tick += milliseconds(SKIP_TICKS);
            loops++;
        }

        interpolation = duration<double, std::milli>(steady_clock::now() + milliseconds(SKIP_TICKS) - next_game_tick).count()
            / double(SKIP_TICKS);
        reflush(interpolation);
    }

    EndBatchDraw();
    closegraph();
}