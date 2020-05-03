#pragma once
#ifndef _BASIC_OBJECT_H_
#define _BASIC_OBJECT_H_


#include <graphics.h>
#include <vector>
#include <functional>
#include <chrono>
#include "Global.h"

#define GRAVITY 0.0036

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
    double x() const;
    double y() const;
    void   x(double x);
    void   y(double y);
    void   set(double x, double y);
};
class Position: public Vector {
    public:
    using Vector::Vector;
    Position():Vector(){}
    Position(const Vector& t) { x(t.x()), y(t.y()); }
    using Vector::operator=;
};
class Velocity: public Vector {
    public:
    using Vector::Vector;
    Velocity():Vector() {}
    Velocity(const Vector& t) { x(t.x()), y(t.y()); }
    using Vector::operator=;
};
class Acceleration: public Vector {
    public:
    using Vector::Vector;
    Acceleration():Vector() {}
    Acceleration(const Vector& t) { x(t.x()), y(t.y()); }
    using Vector::operator=;
};
struct FigureData {
    string name;
    vector<IMAGE> images;
    vector<IMAGE> masks;
    std::function<bool(void)> tigger;
};
using namespace std::chrono;
class Figure {
    private:
        vector<FigureData> figures;
        int figure_cnt = 0;
        steady_clock::time_point time_tick = steady_clock::now();
        int _width;
        int _height;
        string _status;
    public:
        Figure():figures(), figure_cnt(0),_width(0),_height(0),_status("default") {}
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
        string _type;
        int id;
        static int counter;
        bool killed;
    public:
        Position position;
        Velocity velocity;
        Acceleration acceleration;
        Figure figure;
        BaseObject():
            id(counter++),_width(0),_height(0),_type(),position(), velocity(), acceleration(0, GRAVITY), figure(), killed(0) {}
        BaseObject(const double x, const double y):
            id(counter++), _width(0), _height(0), _type(), position(x,y), velocity(), acceleration(0, GRAVITY), figure(), killed(0) {}
        BaseObject(const double x, const double y, int width, int height):
            id(counter++), _width(width), _height(height), _type(), position(x, y), velocity(), acceleration(0, GRAVITY), figure(), killed(0) {}
        BaseObject(const double x, const double y, int width, int height, string type):
            id(counter++), _width(width), _height(height), _type(type), position(x, y), velocity(), acceleration(0, GRAVITY), figure(), killed(0) {}
        ~BaseObject() { counter--; }
        int side_crash = 0;
        int  width();
        int  height();
        int  get_id();
        string type();
        void width(int w);
        void height(int h);
        void type(string t);
        void update(double time);
        void show(Vector& offset);
        virtual void kill();
        bool is_killed();
        virtual void init() = 0;
};


#endif