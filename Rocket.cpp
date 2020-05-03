#include "Rocket.h"



void Rocket::setRocket(int x, int y, int width, int height, string _type)
{
    type(_type);
    position.x(x);
    position.y(y);
    this->width(width);
    this->height(height);
}

void Rocket::init() {
    if(type() == "rock0") return;
    LPCTSTR img_src, mask_src;
    img_src = _T("assets\\images\\rock.png");
    mask_src = _T("assets\\images\\rock_mask.png");
    int figure_num = 7;
    IMAGE origin, organ_mask;
    loadimage(&origin, img_src);
    loadimage(&organ_mask, mask_src);
    int width = origin.getwidth() / figure_num;
    int height = origin.getheight();
    this->width(width);
    this->height(height);
    string names[7] = {"rock1","rock2","rock3","rock4","rock5","rock6","rock7"};
    vector<IMAGE> imgs, masks;
    IMAGE temp;

    for(int i = 0; i < 7; i++) {
        imgs.clear(); masks.clear();
        SetWorkingImage(&origin);
        getimage(&temp, width * i, 0, width, height);
        imgs.push_back(temp);
        SetWorkingImage(&organ_mask);
        getimage(&temp, width * i, 0, width, height);
        masks.push_back(temp);
        figure.addFigure(names[i], imgs, masks, [name = names[i],this]()->bool {
            if(this->type() == name) return true;
            return false;
        });
    }
    SetWorkingImage(NULL);
}
