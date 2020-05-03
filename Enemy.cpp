#include "Enemy.h"

void Enemy::init()
{
    LPCTSTR img_src, mask_src;
    img_src = _T("assets\\images\\enemy.png");
    mask_src = _T("assets\\images\\enemy_mask.png");
    int figure_num = 4;
    IMAGE origin, organ_mask;
    loadimage(&origin, img_src);
    loadimage(&organ_mask, mask_src);
    int width = origin.getwidth() / figure_num;
    int height = origin.getheight();
    this->width(width);
    this->height(height);
    vector<IMAGE> imgs, masks;
    IMAGE temp;

    imgs.clear(); masks.clear();
    for(int i = 0; i < 2; i++) {
        SetWorkingImage(&origin);
        getimage(&temp, 0 + width * i, 0, width, height);
        imgs.push_back(temp);
        SetWorkingImage(&organ_mask);
        getimage(&temp, 0 + width * i, 0, width, height);
        masks.push_back(temp);
    }
    figure.addFigure("running", imgs, masks, [this]()->bool {
        if(!is_killed()) return true;
        return false;
    });



    imgs.clear(); masks.clear();
    for(int i = 2; i < 4; i++) {
        SetWorkingImage(&origin);
        getimage(&temp, 0 + width * i, 0, width, height);
        imgs.push_back(temp);
        SetWorkingImage(&organ_mask);
        getimage(&temp, 0 + width * i, 0, width, height);
        masks.push_back(temp);
    }
    figure.addFigure("killed", imgs, masks, [this]()->bool {
        if(is_killed()) return true;
        return false;
    });
    SetWorkingImage(NULL);

}

void Enemy::kill()
{
    BaseObject::kill();
    kill_tick = steady_clock::now();
}



void Enemy::move_range(double a, double b)
{
    range_left = a;
    range_right = b;
}

double Enemy::move_range_left()
{
    return range_left;
}

double Enemy::move_range_right()
{
    return range_right;
}

bool Enemy::is_removed()
{
    if(is_killed()&&duration<double, std::milli>(steady_clock::now() - kill_tick).count() > 750)
        return true;
    return false;
}
