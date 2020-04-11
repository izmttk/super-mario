#include "Map.h"


void Map::init(BaseObject* h)
{
    loadimage(&background, _T("assets\\images\\map1.png"));
    _width = background.getwidth();
    _height = background.getheight();
    int unit_length = 35;
    //单元格为35*35的方格，全地图横向228个单元，纵向14个单元
    //注意坐标是从0开始的
    rocket.push_back(Rocket(-1 * unit_length, 0 * unit_length, 1 * unit_length, 14 * unit_length));
    rocket.push_back(Rocket(228 * unit_length, 0 * unit_length, 1 * unit_length, 14 * unit_length));
    rocket.push_back(Rocket(0 * unit_length, 12 * unit_length, 69 * unit_length, 2 * unit_length));
    rocket.push_back(Rocket(71 * unit_length, 12 * unit_length, 15 * unit_length, 2 * unit_length));
    rocket.push_back(Rocket(89 * unit_length, 12 * unit_length, 64 * unit_length, 2 * unit_length));
    rocket.push_back(Rocket(155 * unit_length, 12 * unit_length, 73 * unit_length, 2 * unit_length));
    rocket.push_back(Rocket(0 * unit_length, 14 * unit_length, 227 * unit_length, 1 * unit_length));
    for(int i=0;i<4;i++)
        rocket.push_back(Rocket((134+i) * unit_length, (11-i) * unit_length, 1 * unit_length, (i+1) * unit_length));
    for(int i = 0; i < 4; i++)
        rocket.push_back(Rocket((140 + i) * unit_length, (8 + i) * unit_length, 1 * unit_length, (4 - i) * unit_length));
    for(int i = 0; i < 4; i++)
        rocket.push_back(Rocket((148 + i) * unit_length, (11 - i) * unit_length, (5-i) * unit_length, 1 * unit_length));
    for(int i = 0; i < 4; i++)
        rocket.push_back(Rocket((155 + i) * unit_length, (8 + i) * unit_length, 1 * unit_length, (4 - i) * unit_length));
    for(int i = 0; i < 8; i++)
        rocket.push_back(Rocket((181 + i) * unit_length, (11 - i) * unit_length, (9 - i) * unit_length, 1 * unit_length));
    rocket.push_back(Rocket(212 * unit_length, 11 * unit_length, 1 * unit_length, 1 * unit_length));
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
