#pragma once

#define WINDOWS_WIDTH 640
#define WINDOWS_HEIGHT 480

#define DEBUG
#ifdef DEBUG
#include<iostream>
#include<cstdio>
using namespace std;
#endif

#define RUNNING 0
#define STILL 1
#define JUMPPING 2

#define RIGHT 0
#define LEFT 1


#include<utility>
void rotateFlip(IMAGE* img)
{
    DWORD* img_pMem = GetImageBuffer(img);

    for(int y = 0; y< img->getheight(); y++)
    {
        for(int x = 0; x< int(img->getwidth()/2+0.5); x++)
        {
            int num1 = y*img->getwidth()+x;
            int num2 = (y+1)*img->getwidth()-x-1;
            std::swap(img_pMem[num1], img_pMem[num2]);
        }
    }
}


class Vector {
    private:
    double _x;
    double _y;
    public:
    Vector():_x(0), _y(0) {}
    Vector(const double x, const double y):_x(x), _y(y) {}
    Vector(const Vector& v):_x(v._x), _y(v._y) {}
    Vector operator = (const Vector& rhs) {
        _x = rhs._x;
        _y = rhs._y;
    }
    Vector operator + (const Vector& rhs) const {
        return Vector(_x + rhs._x, _y + rhs._y);
    }
    Vector operator - (const Vector& rhs) const {
        return Vector(_x - rhs._x, _y - rhs._y);
    }
    Vector operator * (const double rhs) const {
        return Vector(_x * rhs, _y * rhs);
    }
    Vector operator / (const double rhs) const {
        if(rhs != 0)
            return Vector(_x / rhs, _y / rhs);
    }
    Vector operator += (const Vector& rhs) {
        *this = *this + rhs;
        return *this;
    }
    Vector operator -= (const Vector& rhs) {
        *this = *this - rhs;
        return *this;
    }
    Vector operator *= (const double rhs) {
        *this = *this * rhs;
        return *this;
    }
    Vector operator /= (const double rhs) {
        *this = *this / rhs;
        return *this;
    }
    bool operator == (const Vector& rhs) const {
        if(_x == rhs._x && _y == rhs._y) return true;
        else return false;
    }
    bool operator == (const double rhs) const {
        if(_x == rhs && _y == rhs) return true;
        else return false;
    }
    bool operator != (const Vector& rhs) const {
        if(*this == rhs) return false;
        else return true;
    }
    double x() { return round(_x); }
    double y() { return round(_y); }
    void   x(double x) { _x = x; }
    void   y(double y) { _y = y; }
    void   set(double x, double y) { _x = x, _y = y; }
};
class Position: public Vector {
    public:
    using Vector::Vector;
    Position(const Vector& v):Vector(v) {}
};
class Velocity: public Vector {
    public:
    using Vector::Vector;
    Velocity(const Vector& v):Vector(v) {}
};
class Acceleration: public Vector {
    public:
    using Vector::Vector;
    Acceleration(const Vector& v):Vector(v) {}
};