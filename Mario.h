#pragma once

#include<graphics.h>
#include "Global.h"
#include "BaseObject.h"

#define MARIO_X 0
#define MARIO_Y 343


class Mario: public BaseObject
{
    private:
        int direction;
    public:
        Mario():BaseObject(),direction(RIGHT){}
        void run() {
            if(direction == RIGHT)
                velocity.x(0.3);
            else
                velocity.x(-0.3);
        }
        void jump() {
            velocity.y(-0.7);
        }
        void still() {
            velocity.x(0);
        }
        void turn(int d) {
            if(direction != d) {
                direction = !direction;
                figure.turn();
            }
        }
        void init() {
            LPCTSTR img_src, mask_src;
            img_src = _T("assert\\images\\mario.png");
            mask_src = _T("assert\\images\\mario_mask.png");
            int figure_num = 5;
            IMAGE origin, organ_mask;
            loadimage(&origin, img_src);
            loadimage(&organ_mask, mask_src);
            int width = origin.getwidth() / figure_num;
            int height = origin.getheight();
            vector<IMAGE> imgs,masks;
            IMAGE temp;

            SetWorkingImage(&origin);
            getimage(&temp, 0, 0, width, height);
            imgs.push_back(temp);
            SetWorkingImage(&organ_mask);
            getimage(&temp, 0, 0, width, height);
            masks.push_back(temp);
            figure.addFigure("still", imgs, masks, [this]()->bool{
                if(velocity.x() == 0) return true;
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
                if(velocity.x() != 0 && velocity.y()>=0) return true;
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

};