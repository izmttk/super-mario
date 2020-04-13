#include "BaseObject.h"

Vector Vector::operator = (const Vector& rhs) {
    _x = rhs._x;
    _y = rhs._y;
    return *this;
}
Vector Vector::operator + (const Vector& rhs) const {
    return Vector(_x + rhs._x, _y + rhs._y);
}
Vector Vector::operator - (const Vector& rhs) const {
    return Vector(_x - rhs._x, _y - rhs._y);
}
Vector Vector::operator * (const double rhs) const {
    return Vector(_x * rhs, _y * rhs);
}
Vector Vector::operator / (const double rhs) const {
    return Vector(_x / rhs, _y / rhs);
}
Vector Vector::operator += (const Vector& rhs) {
    *this = *this + rhs;
    return *this;
}
Vector Vector::operator -= (const Vector& rhs) {
    *this = *this - rhs;
    return *this;
}
Vector Vector::operator *= (const double rhs) {
    *this = *this * rhs;
    return *this;
}
Vector Vector::operator /= (const double rhs) {
    *this = *this / rhs;
    return *this;
}
bool Vector::operator == (const Vector& rhs) const {
    if(_x == rhs._x && _y == rhs._y) return true;
    else return false;
}
bool Vector::operator == (const double rhs) const {
    if(_x == rhs && _y == rhs) return true;
    else return false;
}
bool Vector::operator != (const Vector& rhs) const {
    if(*this == rhs) return false;
    else return true;
}
double Vector::x() const { return (_x); }
double Vector::y() const { return (_y); }
void   Vector::x(double x) { _x = x; }
void   Vector::y(double y) { _y = y; }
void   Vector::set(double x, double y) { _x = x, _y = y; }

void Figure::addFigure(string name, vector<IMAGE> imgs, vector<IMAGE> masks, function<bool(void)> tigger) {
    if(figures.empty() && !imgs.empty()) {
        _width = imgs.front().getwidth();
        _height = imgs.front().getheight();
    }
    figures.push_back(FigureData{name, imgs, masks, tigger});
}
void Figure::update(int x, int y) {
    for(auto& i : figures)
    {
        if(i.tigger()) {
            if(i.name!="rock0"&&i.name!="rock1")
            //cout << i.name << endl;
            if(_status != i.name) {
                time_tick = steady_clock::now();
                figure_cnt = 0;
                _status = i.name;
            }
            //cout << figure_cnt << endl;
            //没人发现我写的bug
            putimage(x, y, &i.masks[figure_cnt % i.images.size()], NOTSRCERASE);
            putimage(x, y, &i.images[figure_cnt % i.images.size()], SRCINVERT);
            if((steady_clock::now() - time_tick) >= milliseconds(100)) {
                figure_cnt = (figure_cnt + 1) % i.images.size();
                time_tick = steady_clock::now();
            }
            return;
        }
    }
}
void Figure::turn() {
    for(auto& i : figures)
    {
        for(auto& j : i.images) rotateFlip(&j);
        for(auto& j : i.masks)  rotateFlip(&j);
    }
}
string Figure::status()
{
    return _status;
}
void Figure::status(string s)
{
    _status = s;
}
int Figure::width() {
    return _width;
}
int Figure::height() {
    return _height;
}

int  BaseObject::width() {
    return _width;
}
int  BaseObject::height() {
    return _height;
}
void BaseObject::width(int w) {
    _width = w;
}
void BaseObject::height(int h) {
    _height = h;
}
void BaseObject::update(double time) {
    position += (velocity * time + acceleration * time * time / 2);
    //position += velocity * time;
    velocity += acceleration * time;
}
void BaseObject::show(Vector& offset) {
    figure.update(static_cast<int>(round(position.x()) + offset.x()), static_cast<int>(round(position.y()) + offset.y()));
}


