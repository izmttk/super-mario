#include "Mario.h"

void Mario::run(double speed) {
    if(direction == RIGHT)
        velocity.x(speed);
    else
        velocity.x(-speed);
}

void Mario::jump(double speed) {
    if(figure.status() == "jumpping" || figure.status() == "falling") return;
    position.y(position.y());
    velocity.y(speed);
}

void Mario::still() {
    velocity.x(0);
}

void Mario::turn(int d) {
    if(direction != d) {
        direction = !direction;
        figure.turn();
    }
}

void Mario::init() {
    LPCTSTR img_src, mask_src;
    img_src = _T("assets\\images\\mario.png");
    mask_src = _T("assets\\images\\mario_mask.png");
    int figure_num = 5;
    IMAGE origin, organ_mask;
    loadimage(&origin, img_src);
    loadimage(&organ_mask, mask_src);
    int width = origin.getwidth() / figure_num;
    int height = origin.getheight();
    this->width(width);
    this->height(height);
    vector<IMAGE> imgs, masks;
    IMAGE temp;

    for(int i = 0; i < 3; i++) {
        SetWorkingImage(&origin);
        getimage(&temp, width + width * i, 0, width, height);
        imgs.push_back(temp);
        SetWorkingImage(&organ_mask);
        getimage(&temp, width + width * i, 0, width, height);
        masks.push_back(temp);
    }
    figure.addFigure("running", imgs, masks, [this]()->bool {
        if(velocity.x() != 0 && velocity.y() == 0) return true;
        return false;
    });

    imgs.clear(); masks.clear();
    SetWorkingImage(&origin);
    getimage(&temp, 0, 0, width, height);
    imgs.push_back(temp);
    SetWorkingImage(&organ_mask);
    getimage(&temp, 0, 0, width, height);
    masks.push_back(temp);
    figure.addFigure("still", imgs, masks, [this]()->bool {
        if(velocity.x() == 0 && velocity.y() == 0)  return true;
        return false;
    });
    figure.addFigure("falling", imgs, masks, [this]()->bool {
        if(velocity.y() > 0) return true;
        return false;
    });

    imgs.clear(); masks.clear();
    SetWorkingImage(&origin);
    getimage(&temp, width * 4, 0, width, height);
    imgs.push_back(temp);
    SetWorkingImage(&organ_mask);
    getimage(&temp, width * 4, 0, width, height);
    masks.push_back(temp);
    figure.addFigure("jumpping", imgs, masks, [this]()->bool {
        if(velocity.y() < 0) return true;
        return false;
    });

    SetWorkingImage(NULL);
}
