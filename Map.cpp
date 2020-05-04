#include "Map.h"
#include "Controller.h"
#include <algorithm>
extern Controller ctl;
void Map::init(BaseObject* h)
{
    hero = h;

    loadimage(&background, _T("assets\\images\\map1.png"));
    _width = background.getwidth();
    _height = background.getheight();
    //单元格为35*35的方格，全地图横向228个单元，纵向14个单元
    //注意坐标是从0开始的
    //测试用
    object.clear();
    //add_rocket(0, 10, 1, 1, "rock1");
    //add_rocket(0, 11, 1, 1, "rock1");
    //add_rocket(2, 10, 1, 1, "rock1");
    //add_rocket(2, 11, 1, 1, "rock1");

    //铺垫底层基石
    add_rocket(-1, 0, 1, 14);
    add_rocket(228, 0, 1, 14);
    add_rocket(0, 12, 69, 2);
    add_rocket(71, 12, 15, 2);
    add_rocket(89, 12, 64, 2);
    add_rocket(155, 12, 73, 2);
    add_rocket(0, 14, 227, 1);
    
    //铺垫默认山丘
    for(int i=0;i<4;i++) add_rocket((134+i), (11-i), 1, (i+1));
    for(int i = 0; i < 4; i++) add_rocket((140 + i), (8 + i), 1, (4 - i));
    for(int i = 0; i < 4; i++) add_rocket((148 + i), (11 - i), (5-i), 1);
    for(int i = 0; i < 4; i++) add_rocket((155 + i), (8 + i), 1, (4 - i));
    for(int i = 0; i < 8; i++) add_rocket((181 + i), (11 - i), (9 - i), 1);
    add_rocket(212, 11, 1, 1);

    //铺垫漂浮岩石
    add_rocket(16, 8, 1, 1, "rock1");
    for(int i = 0; i < 5; i++) add_rocket((20 + i), 8, 1, 1, "rock1");
    add_rocket(22 , 4 , 1 , 1 , "rock1");
    for(int i = 0; i < 3; i++) add_rocket((77 + i), 8, 1, 1, "rock1");
    for(int i = 0; i < 8; i++) add_rocket((80 + i), 4, 1, 1, "rock1");
    for(int i = 0; i < 4; i++) add_rocket((91 + i), 4, 1, 1, "rock1");
    add_rocket(94, 8, 1, 1, "rock1");
    add_rocket(100, 8, 1, 1, "rock1");
    add_rocket(106, 8, 1, 1, "rock1");
    add_rocket(109, 4, 1, 1, "rock1");
    add_rocket(109, 8, 1, 1, "rock1");
    add_rocket(112, 8, 1, 1, "rock1");
    add_rocket(117, 8, 1, 1, "rock1");
    for(int i = 0; i < 3; i++) add_rocket((120 + i), 4, 1, 1, "rock1");
    for(int i = 0; i < 4; i++) add_rocket((127 + i), 4, 1, 1, "rock1");
    for(int i = 0; i < 2; i++) add_rocket((128 + i), 8, 1, 1, "rock1");
    for(int i = 0; i < 4; i++) add_rocket((168 + i), 8, 1, 1, "rock1");

    for(auto i : object) i->init();


    //安放管道
    add_pipe(28, 10, 2, 2);
    add_pipe(38, 9, 2, 3);
    add_pipe(46, 8, 2, 4);
    add_pipe(57, 8, 2, 4);
    add_pipe(163, 10, 2, 2);
    add_pipe(179, 10, 2, 2);

    enemy.clear();
    add_enemy(6, 11, 6, 14);
    add_enemy(20, 7, 20, 24);
    add_enemy(40, 11, 40, 45);
    add_enemy(57, 7, 57, 58);
    add_enemy(71, 11, 71, 76);
    add_enemy(85, 3, 80, 85);
    add_enemy(97, 11, 95, 99);
    add_enemy(112, 7, 112, 112);
    add_enemy(123, 11, 123, 133);
    add_enemy(171, 11, 171, 175);
    add_enemy(190, 11, 190, 211, 0.2);
    add_enemy(193, 11, 190, 211, 0.3);
    add_enemy(193, 11, 190, 211, 0.3);
    add_enemy(196, 11, 190, 211, 0.1);
    add_enemy(199, 11, 190, 211, 0.15);
    add_enemy(211, 11, 190, 211, 0.25);

    for(auto i : enemy) i->init();

}

void Map::show(Vector offset)
{
    putimage(0 + static_cast<int>(offset.x()), 0 + static_cast<int>(offset.y()), &background);
    for(auto i: object)
        i->show(offset);
    for(auto i : enemy)
        i->show(offset);

}
int Map::width() {
    return _width;
}
int Map::height() {
    return _height;
}
void Map::update(double time)
{
    for(auto i : enemy) {
        if(i->position.x() < i->move_range_left())
            i->velocity.x(-i->velocity.x());
        if(i->position.x() > i->move_range_right())
            i->velocity.x(-i->velocity.x());
        i->update(time);
    }
    remove_if(enemy.begin(), enemy.end(), [](Enemy* val) {return val->is_removed();});
    check_collision();
}

bool Map::left_exist(BaseObject &t)
{
    for(auto i : object)
        if(t.position.x() == i->position.x() + i->width() && t.position.y() == i->position.y())
            return true;
    return false;
}

bool Map::right_exist(BaseObject& t)
{
    for(auto i : object)
        if(t.position.x() + t.width() == i->position.x() && t.position.y() == i->position.y())
            return true;
    return false;
}

void Map::check_collision()
{
    int flag = 0;
    double x1 = hero->position.x() - unit_length,
           y1 = hero->position.y() - unit_length,
           x2, y2;
    int w1 = hero->width(),
        h1 = hero->height(),
        w2, h2;
    for(auto i : object) {
        x2 = i->position.x() - unit_length;
        y2 = i->position.y() - unit_length;
        w2 = i->width();
        h2 = i->height();
        if(fabs(x1 + w1 - x2 - w2) < w1 + w2 && fabs(y1 + h1 - y2 - h2) < h1 + h2)
        {
            bool l = left_exist(*i),
                r = right_exist(*i);
            string str = collision(*hero, *i, l, r);
            if(str == "left")
                flag = (1 << 1) | flag;//0没有 1右 2左 3左右
            if(str == "right")
                flag = (1 << 0) | flag;
            if(str != "") {
                //cout << str <<' '<<i.type()<<' '<<i.position.x()/36<<' '<<i.position.y()/36<< endl;
                if(str == "top") {
                    if(hero->velocity.y() > 0)
                        hero->velocity.y(0);
                    hero->position.y(i->position.y() - hero->height());
                }
                else if(str == "bottom") {
                    if(hero->velocity.y() < 0)
                        hero->velocity.y(0);
                    hero->position.y(i->position.y() + i->height());
                }
                else if(str == "left") {
                    if(hero->velocity.x() > 0)
                        hero->velocity.x(0);
                    hero->position.x(i->position.x() - hero->width());
                }
                else if(str == "right") {
                    if(hero->velocity.x() < 0)
                        hero->velocity.x(0);
                    hero->position.x(i->position.x() + i->width());
                }
            }
        }
    }
    for(auto i : enemy) {
        x2 = i->position.x() - unit_length;
        y2 = i->position.y() - unit_length;
        w2 = i->width();
        h2 = i->height();
        if(!i->is_killed() && (fabs(x1 + w1 - x2 - w2) < w1 + w2 && fabs(y1 + h1 - y2 - h2) < h1 + h2))
        {
            string str = collision(*hero, *i, 0, 0);
            if(str == "top") {
                i->kill();
                ctl.play_music("killenemy");
            }
            else if(str == "left" || str == "right") {
                hero->kill();
            }
        }
    }
    if(flag) hero->side_crash = flag;
    else hero->side_crash = 0;
}

void Map::add_rocket(int x, int y, int width, int height, string type)
{
    Rocket* p = new Rocket(x * unit_length, y * unit_length, width * unit_length, height * unit_length, type);
    object.push_back(p);

}

void Map::add_pipe(int x, int y, int width, int height)
{
    Pipe* p = new Pipe(x * unit_length, y * unit_length, width * unit_length, height * unit_length);
    object.push_back(p);
}

void Map::add_enemy(int x, int y, int range_left, int range_right, double v)
{
    Enemy* p = new Enemy(x * unit_length, y * unit_length, range_left * unit_length, range_right * unit_length);
    p->acceleration.y(0);
    p->velocity.x(v);
    enemy.push_back(p);
}


string Map::collision(BaseObject &a,BaseObject &b,bool left_exist,bool right_exist) {

    int ax = static_cast<int>(round(a.position.x())),
        ay = static_cast<int>(round(a.position.y())),
        bx = static_cast<int>(round(b.position.x())),
        by = static_cast<int>(round(b.position.y()));
    //上碰撞(a相对被撞物体b)
    if(ax + a.width() > bx && ax < bx + b.width() &&
       ay + a.height() >= by && ay < by) {
        if(a.position.x() < b.position.x() && a.position.x() + a.width() < b.position.x() + b.width() && a.position.x() + a.width() - b.position.x() < a.position.y() + a.height() - b.position.y())
            return "left";
        if(a.position.x() > b.position.x() && a.position.x() + a.width() > b.position.x() + b.width() && b.position.x() + b.width() - a.position.x() < a.position.y() + a.height() - b.position.y())
            return "right";
        return "top";
    }
    //下碰撞
    else if(ax + a.width() > bx && ax < bx + b.width() &&
       ay + a.height() > by + b.height() && ay < by + b.height()) {
        if(a.position.x() < b.position.x() && a.position.x() + a.width() < b.position.x() + b.width() && a.position.x() + a.width() - b.position.x() < b.position.y() + b.height() - a.position.y())
            return "left";
        if(a.position.x() > b.position.x() && a.position.x() + a.width() > b.position.x() + b.width() && b.position.x() + b.width() - a.position.x() < b.position.y() + b.height() - a.position.y())
            return "right";
        return "bottom";
    }
    //左碰撞
    else if(ax + a.width() >= bx && ax < bx &&
       ay + a.height() >= by && ay < by + b.height()) {
        if(!left_exist) {
            return "left";
        }
    }
    //右碰撞
    else if(ax + a.width() > bx + b.width() && ax <= bx + b.width() &&
       ay + a.height() >= by && ay < by + b.height()) {
        if(!right_exist) {
            //cout << "a.x:" << ax << "\t\ta.y:" << ay << "\t\ta.width:" << a.width() << "\ta.height:" << a.height() << endl;
            //cout << "b.x:" << bx << "\t\tb.y:" << by << "\t\tb.width:" << b.width() << "\tb.height:" << b.height() << endl;
            return "right";
        }
    }
    return "";
}