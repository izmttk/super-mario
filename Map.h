#pragma once

#include<graphics.h>
#include "Global.h"

class Map
{
    private:
        IMAGE background;
    public:
        Map();
        ~Map();
        void loadResource();
        void show();

};

Map::Map()
{

}

Map::~Map()
{

}

inline void Map::loadResource()
{
    loadimage(&background, _T("assert\\images\\map1.png"));
}

inline void Map::show()
{
    putimage(0, 0, &background);
}
