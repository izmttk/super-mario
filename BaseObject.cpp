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
double Vector::x() { return (_x); }
double Vector::y() { return (_y); }
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
            using namespace std::chrono;
            static auto time_tick = steady_clock::now();
            static size_t cnt = 0;
            if(_status != i.name) {
                time_tick = steady_clock::now();
                cnt = 0;
                _status = i.name;
            }
            putimage(x, y, &i.masks[i.images.size() - cnt - 1], NOTSRCERASE);
            putimage(x, y, &i.images[i.images.size() - cnt - 1], SRCINVERT);
            if((steady_clock::now() - time_tick) >= milliseconds(100)) {
                cnt = (cnt + 1) % i.images.size();
                time_tick = steady_clock::now();
            }

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
void BaseObject::show(Vector offset) {
    figure.update(static_cast<int>(round(position.x()) + offset.x()), static_cast<int>(round(position.y()) + offset.y()));
}
bool BaseObject::block_crash(BaseObject& t) {
    //if(
    //    position.x() > t.position.x() - figure.width() && position.x() < t.position.x() + t.figure.width()
    //    &&
    //    position.y() > t.position.y() - figure.height() && position.y() < t.position.y() + t.figure.height()
    //    )
    //    return true;
    //cout << t.position.x() << " " << t.position.y() << endl;
    int px = static_cast<int>(round(position.x())),
        py = static_cast<int>(round(position.y())), 
        tpx = static_cast<int>(round(t.position.x())),
        tpy = static_cast<int>(round(t.position.y()));

    //ÉÏÅö×²(Ïà¶Ô±»×²ÎïÌå)
    if(px + width() -1 >= tpx && px <= tpx + t.width() -1 &&
       py + height() >= tpy && py < tpy) {
        if(velocity.y() > 0) {
            velocity.y(0);
            position.y((double)tpy - height());
        }
        return true;
    }
    //ÏÂÅö×²
    if(px + width() -1 >= tpx && px <= tpx + t.width() -1 &&
       py + height() -1 > tpy + height() -1 && py <= tpy + t.height()) {
        if(velocity.y() < 0) {
            velocity.y(0);
            position.y((double)tpy + t.height());
        }
        return true;
    }
    //×óÅö×²
    if(px + width() >= tpx && px < tpx &&
       py + height() >= tpy && py <= tpy + t.height()) {
        if(velocity.x() > 0) {
            velocity.x(0);
            position.x((double)tpx - width());
        }
        return true;
    }
    //ÓÒÅö×²
    if(px + width() > tpx + t.width()&& px <= tpx + t.width() &&
       py + height() >= tpy && py <= tpy + t.height()) {
        if(velocity.x() < 0) {
            velocity.x(0);
            position.x((double)tpx + t.width());
        }
        return true;
    }
    return false;
}
//bool BaseObject::pxiel_crash() {
//
//}


