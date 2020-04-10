#include<conio.h>
#include<ctime>
#include <chrono>   
#include "Mario.h"
#include "Map.h"
//#include "Controller.h"

Mario mario;
Map map;
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
void reflush(double x) {
    mario.update(x);
    map.update();
    cleardevice();
    map.show();
    mario.show();
    FlushBatchDraw();
    //_getch();
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