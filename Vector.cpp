
/*
    Vector.cpp
*/

#include "Types.h"
#include <cmath>

namespace Vi {

    /* Vec2i */

    Vec2i::Vec2i() { x = 0; y = 0; }
    Vec2i::Vec2i(int x, int y) { this->x = x; this->y = y; }

    double Vec2i::hypot(const Vec2i& vec) { return std::hypot(vec.x, vec.y); }
    int Vec2i::cross(const Vec2i& a, const Vec2i& b) {
        return (a.x * b.y) - (a.y * b.x);
    }


    Vec2f::Vec2f() { x = 0.0f; y = 0.0f; }
    Vec2f::Vec2f(float x, float y) { this->x = x; this->y = y; }



    Vec2d::Vec2d() { x = 0.0; y = 0.0; }
    Vec2d::Vec2d(double x, double y) { this->x = x; this->y = y; }
}

