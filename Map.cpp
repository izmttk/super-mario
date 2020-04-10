#include "Map.h"


void Map::init(BaseObject* h)
{
    loadimage(&background, _T("assert\\images\\map1.png"));
    //注意坐标是从0开始的
    rocket.push_back(Rocket(-1, 0, 1, WINDOWS_HEIGHT));
    rocket.push_back(Rocket(7818, 0, 1, WINDOWS_HEIGHT));
    rocket.push_back(Rocket(0, 411, 2366, 69));
    rocket.push_back(Rocket(2434, 411, 515, 69));
    rocket.push_back(Rocket(3051, 411, 2195, 69));
    rocket.push_back(Rocket(5314, 411, 2503, 69));
    hero = h;
}

void Map::show()
{
    putimage(0, 0, &background);
}

void Map::update()
{
    check_crash();
}

void Map::check_crash()
{
    for(auto& i : rocket) {
        hero->block_crash(i);
    }
}
