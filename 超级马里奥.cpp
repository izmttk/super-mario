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
    double speed = NORMAL_RUN_SPEED;
    double jump = NORMAL_JUMP_SPEED;

    if(GetAsyncKeyState(VK_SHIFT)) {
        speed += 0.5;
        jump -= 0.5;
    }
    if(GetAsyncKeyState(VK_SPACE) || GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT)) {
        if(GetAsyncKeyState(VK_SPACE))
            mario.jump(jump);
        if(GetAsyncKeyState(VK_LEFT))
            mario.turn(LEFT), mario.run(speed);
        if(GetAsyncKeyState(VK_RIGHT))
            mario.turn(RIGHT), mario.run(speed);
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

    const int max_ups = 240;
    const int max_fps = 120;

    const int update_skip_time = 1000 / max_ups;
    const int frame_skip_time = 1000 / max_fps;

    using namespace std::chrono;

    auto update_time_tick = steady_clock::now();
    auto frame_time_tick = steady_clock::now();

    double update_time_interval;
    double frame_time_interval;

    bool game_is_running = true;
    while(game_is_running) {
        auto now = steady_clock::now();
        update_time_interval = duration<double, std::milli>(now - update_time_tick).count();
        if(update_time_interval >= update_skip_time) {
            update();
            update_time_tick = now;
        }
        frame_time_interval = duration<double, std::milli>(now - frame_time_tick).count();
        if(frame_time_interval >= frame_skip_time) {
            reflush(frame_time_interval);
            frame_time_tick = now;
        }
    }

    EndBatchDraw();
    closegraph();
}