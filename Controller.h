#pragma once

#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
#include "Global.h"
#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib")
#include <windows.h>

class Controller
{
    private:

    public:
        void welcome();
        void win();
        void lose();
        void play_music(string type);
        void show_welcome_ui();
        void show_gaming_ui();
        void show_lose_ui();
        void show_help_ui();
};


#endif