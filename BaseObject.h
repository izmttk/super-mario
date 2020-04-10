#pragma once
#include "Global.h"
#include<vector>
#include<functional>

struct FigureData {
    string name;
    vector<IMAGE> images;
    vector<IMAGE> masks;
    std::function<bool(void)> tigger;
};
class Figure {
    private:
    vector<FigureData> figures;
    int width;
    int height;
    string status;
    public:
    void addFigure(string name, vector<IMAGE> imgs, vector<IMAGE> masks, function<bool(void)> tigger) {
        if(figures.empty() && !imgs.empty()) {
            width = imgs.front().getwidth();
            height = imgs.front().getheight();
        }
        figures.push_back({name, imgs, masks, tigger});
    }
    void update(int x, int y) {
        for(auto& i : figures)
        {
            if(i.tigger()) {
                static int cnt = 0;
                if(status != i.name) {
                    cnt = 0;
                    status = i.name;
                }
                putimage(x, y, &i.masks[cnt], NOTSRCERASE);
                putimage(x, y, &i.images[cnt], SRCINVERT);
                cnt = (cnt + 1) / i.images.size();
            }
        }
    }
    void turn() {
        for(auto& i : figures)
        {
            for(auto& j : i.images) rotateFlip(&j);
            for(auto& j : i.masks)  rotateFlip(&j);
        }
    }
};


class BaseObject
{
    protected:
        Position position;
        Velocity velocity;
        Acceleration acceleration;
        Figure figure;
    public:
        void update(int time) {
            velocity += acceleration * time;
            position += velocity * time;
        }
};
