#include "Mario.h"

void Mario::run(double speed) {
    if(direction == RIGHT)
        velocity.x(speed);
    else
        velocity.x(-speed);
    if(side_crash == 1 && velocity.x() < 0)velocity.x(0);
    if(side_crash == 2 && velocity.x() > 0)velocity.x(0);
    if(side_crash == 3)velocity.x(0);

}

void Mario::jump(double speed) {
    if(figure.status() == "jumpping" || figure.status() == "falling") return;
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
    direction = RIGHT;
    position.x(MARIO_X);
    position.y(MARIO_Y);
    velocity.x(0);
    velocity.y(0);
    acceleration.x(0);
    acceleration.y(GRAVITY);
    revive();
    figure.clear();

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

    SetWorkingImage(&origin);
    getimage(&temp, 0, 0, width, height);
    imgs.push_back(temp);
    SetWorkingImage(&organ_mask);
    getimage(&temp, 0, 0, width, height);
    masks.push_back(temp);
    figure.addFigure("still", imgs, masks, [this]()->bool {
        if(figure.status() == "jumpping") return false;
        if(velocity.x() == 0 && velocity.y() == 0)  return true;
        return false;
    });
    figure.addFigure("falling", imgs, masks, [this]()->bool {
        if(velocity.y() > 0) return true;
        return false;
    });
    imgs.clear(); masks.clear();
    for(int i = 0; i < 3; i++) {
        SetWorkingImage(&origin);
        getimage(&temp, width + width * i, 0, width, height);
        imgs.push_back(temp);
        SetWorkingImage(&organ_mask);
        getimage(&temp, width + width * i, 0, width, height);
        masks.push_back(temp);
    }
    figure.addFigure("running", imgs, masks, [this]()->bool {
        if(figure.status() == "jumpping") return false;
        if(velocity.x() != 0 && velocity.y() == 0) return true;
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

void Mario::kill()
{
    BaseObject::kill();
}

bool Mario::is_win()
{
    if(position.x() >= 220 * unit_length && position.x() <= 221 * unit_length && position.y() >= 10 * unit_length && position.y() <= 12 * unit_length)
        return true;
    return false;
}
