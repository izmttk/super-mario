#include "Map.h"


void Map::init(BaseObject* h)
{
    loadimage(&background, _T("assets\\images\\map1.png"));
    _width = background.getwidth();
    _height = background.getheight();
    //注意坐标是从0开始的
    rocket.push_back(Rocket(-1, 0, 1, WINDOWS_HEIGHT));
    rocket.push_back(Rocket(7818, 0, 1, WINDOWS_HEIGHT));
    rocket.push_back(Rocket(0, 411, 2366, 69));
    rocket.push_back(Rocket(2434, 411, 515, 69));
    rocket.push_back(Rocket(3051, 411, 2195, 69));
    rocket.push_back(Rocket(5314, 411, 2503, 69));
    hero = h;
}

void Map::show(Vector offset)
{
    putimage(0 + static_cast<int>(offset.x()), 0 + static_cast<int>(offset.y()), &background);
}
int Map::width() {
    return _width;
}
int Map::height() {
    return _height;
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
