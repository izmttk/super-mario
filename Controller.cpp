#include "Controller.h"

void Controller::play_music(string type)
{
    if(type == "welcome") {
        mciSendString(_T("close all"), NULL, 0, NULL);//Õ£÷πÀ˘”–“Ù¿÷
        mciSendString(_T("open \"assets\\audios\\bg.mp3\" alias welcome"), NULL, 0, NULL);//ª∂”≠“Ù¿÷
        mciSendString(_T("play welcome repeat"), NULL, 0, NULL);//—≠ª∑≤•∑≈
    }
    else if(type == "gaming") {
        mciSendString(_T("close all"), NULL, 0, NULL);//Õ£÷πÀ˘”–“Ù¿÷
        mciSendString(_T("open \"assets\\audios\\bg.mp3\" alias gaming"), NULL, 0, NULL);//±≥æ∞“Ù¿÷
        mciSendString(_T("play gaming"), NULL, 0, NULL);//—≠ª∑≤•∑≈
    }
    else if(type == "accele") {
        mciSendString(_T("stop gaming"), NULL, 0, NULL);//Õ£÷πÀ˘”–“Ù¿÷
        mciSendString(_T("open \"assets\\audios\\bg_accele.mp3\" alias accele"), NULL, 0, NULL);//±≥æ∞“Ù¿÷º”ÀŸ
        mciSendString(_T("play accele"), NULL, 0, NULL);//—≠ª∑≤•∑≈
    }
    else if(type == "jump") {
        mciSendString(_T("close jump"), NULL, 0, NULL);
        mciSendString(_T("open \"assets\\audios\\jump.mp3\" alias jump"), NULL, 0, NULL);//Ã¯‘æ“Ù¿÷
        mciSendString(_T("play jump"), NULL, 0, NULL);//—≠ª∑≤•∑≈
    }
    else if(type == "win") {
        mciSendString(_T("close all"), NULL, 0, NULL);//Õ£÷πÀ˘”–“Ù¿÷
        mciSendString(_T("open \"assets\\audios\\win.mp3\" alias win"), NULL, 0, NULL);// §¿˚“Ù¿÷
        mciSendString(_T("play win"), NULL, 0, NULL);//—≠ª∑≤•∑≈
    }
    else if(type == "mario death") {
        mciSendString(_T("close all"), NULL, 0, NULL);//Õ£÷πÀ˘”–“Ù¿÷
        mciSendString(_T("open \"assets\\audios\\mario_death.mp3\" alias mario_death"), NULL, 0, NULL);// ß∞‹“Ù¿÷
        mciSendString(_T("play mario_death"), NULL, 0, NULL);//—≠ª∑≤•∑≈
    }
    else if(type == "enemy death") {
        mciSendString(_T("close enemy_death"), NULL, 0, NULL);
        mciSendString(_T("open \"assets\\audios\\enemy_death.mp3\" alias enemy_death"), NULL, 0, NULL);//“∞π÷À¿Õˆ“Ù¿÷
        mciSendString(_T("play enemy_death"), NULL, 0, NULL);//—≠ª∑≤•∑≈
    }
}
