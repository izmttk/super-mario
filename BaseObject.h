#pragma once
#ifndef _BASIC_OBJECT_H_
#define _BASIC_OBJECT_H_


#include <graphics.h>
#include <vector>
#include <functional>
#include <chrono>
#include "Global.h"



class Vector {
    private:
    double _x;
    double _y;
    public:
    Vector():_x(0), _y(0) {}
    Vector(const double x, const double y):_x(x), _y(y) {}
    Vector(const Vector& v):_x(v._x), _y(v._y) {}
    Vector operator = (const Vector& rhs);
    Vector operator + (const Vector& rhs) const;
    Vector operator - (const Vector& rhs) const;
    Vector operator * (const double rhs) const;
    Vector operator / (const double rhs) const;
    Vector operator += (const Vector& rhs);
    Vector operator -= (const Vector& rhs);
    Vector operator *= (const double rhs);
    Vector operator /= (const double rhs);
    bool operator == (const Vector& rhs) const;
    bool operator == (const double rhs) const;
    bool operator != (const Vector& rhs) const;
    double x();
    double y();
    void   x(double x);
    void   y(double y);
    void   set(double x, double y);
};
class Position: public Vector {
    public:
    using Vector::Vector;
    using Vector::operator=;
};
class Velocity: public Vector {
    public:
    using Vector::Vector;
    using Vector::operator=;
};
class Acceleration: public Vector {
    public:
    using Vector::Vector;
    using Vector::operator=;
};
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
        string _status;
    public:
        Figure():figures(),_width(0),_height(0),_status("default") {}
        void addFigure(string name, vector<IMAGE> imgs, vector<IMAGE> masks, function<bool(void)> tigger);
        void update(int x, int y);
        void turn();
        string status();
        void status(string s);
        int  width();
        int  height();
};


class BaseObject
{
    private:
        int _width;
        int _height;
    public:
        Position position;
        Velocity velocity;
        Acceleration acceleration;
        Figure figure;
        BaseObject():_width(0),_height(0),position(), velocity(), acceleration(0, 0.004), figure(){}
        int  width();
        int  height();
        void width(int w);
        void height(int h);
        void update(double time);
        void show(Vector offset);
        bool block_crash(BaseObject& t);
        bool pxiel_crash();
};


#endif