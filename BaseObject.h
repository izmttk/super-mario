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
        int _width;
        int _height;
        string status;
    public:
        Figure():figures(),_width(0),_height(0),status("default") {}
        void addFigure(string name, vector<IMAGE> imgs, vector<IMAGE> masks, function<bool(void)> tigger) {
            if(figures.empty() && !imgs.empty()) {
                _width = imgs.front().getwidth();
                _height = imgs.front().getheight();
            }
            figures.push_back(FigureData{name, imgs, masks, tigger});
        }
        void update(int x, int y) {
            for(auto& i : figures)
            {
                if(i.tigger()) {
                    using namespace std::chrono;
                    static auto time_tick = steady_clock::now();
                    static int cnt = 0;
                    if(status != i.name) {
                        time_tick = steady_clock::now();
                        cnt = 0;
                        status = i.name;
                    }
                    putimage(x, y, &i.masks[i.images.size()-cnt-1], NOTSRCERASE);
                    putimage(x, y, &i.images[i.images.size()-cnt-1], SRCINVERT);
                    if((steady_clock::now() - time_tick) >= milliseconds(100)) {
                        cnt = (cnt + 1) % i.images.size();
                        time_tick = steady_clock::now();
                    }

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
        int width() {
            return _width;
        }
        int height() {
            return _height;
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
        BaseObject():position(), velocity(), acceleration(0, 0.004), figure(){}
        void update(double time) {
            position += (velocity * time + acceleration * time * time / 2);
            velocity += acceleration * time;
        }
        void show() {
            figure.update(position.x(), position.y());
        }
        bool block_crash(BaseObject & t) {
            if(
                position.x() > t.position.x() - figure.width() && position.x() < t.position.x() + t.figure.width()
                &&
                position.y() > t.position.y() - figure.height() && position.y() < t.position.y() + t.figure.height()
                )
                return true;
            return false;
        }
        bool pxiel_crash() {

        }
};
