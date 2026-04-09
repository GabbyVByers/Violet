
/*
    Vector.cpp
*/

#include "Logger.h"
#include "Types.h"
#include <cmath>

namespace Vi {

    static void zero_error() {
        std::cerr << Vi::Logger::error_message("Division by zero");
        std::terminate();
    }
    static void zero(int x)    { if (x == 0)    { zero_error(); } }
    static void zero(float x)  { if (x == 0.0f) { zero_error(); } }
    static void zero(double x) { if (x == 0.0)  { zero_error(); } }
    
    /* Vec2i */

    Vec2i::Vec2i(int x, int y) { this->x = x; this->y = y; }

    double Vec2i::hypot(const Vec2i& vec) { return std::hypot(vec.x, vec.y); }
    int    Vec2i::cross(const Vec2i& a, const Vec2i& b) { return (a.x * b.y) - (a.y * b.x); }
    int    Vec2i::dot(const Vec2i& a, const Vec2i& b) { return (a.x * b.x) + (a.y * b.y); }

    Vec2i::Vec2i(const Vec2f& vec) { x = (int)vec.x; y = (int)vec.y; }
    Vec2i::Vec2i(const Vec2d& vec) { x = (int)vec.x; y = (int)vec.y; }
    Vec2i& Vec2i::operator = (const Vec2f& vec) { x = (int)vec.x; y = (int)vec.y; return *this; }
    Vec2i& Vec2i::operator = (const Vec2d& vec) { x = (int)vec.x; y = (int)vec.y; return *this; }
    
    Vec2i  Vec2i::operator +  (const Vec2i& vec) const { return Vec2i(x + vec.x, y + vec.y); }
    Vec2i  Vec2i::operator -  (const Vec2i& vec) const { return Vec2i(x - vec.x, y - vec.y); }
    Vec2i  Vec2i::operator *  (const int scale)  const { return Vec2i(x * scale, y * scale); }
    Vec2i  Vec2i::operator /  (const int scale)  const { zero(scale); return Vec2i(x / scale, y / scale); }
    Vec2i& Vec2i::operator += (const Vec2i& vec) { x += vec.x; y += vec.y; return *this; }
    Vec2i& Vec2i::operator -= (const Vec2i& vec) { x -= vec.x; y -= vec.y; return *this; }
    Vec2i& Vec2i::operator *= (const int scale)  { x *= scale; y *= scale; return *this; }
    Vec2i& Vec2i::operator /= (const int scale)  { zero(scale); x /= scale; y /= scale; return *this; }

    /* Vec2f */
    
    Vec2f::Vec2f(float x, float y) { this->x = x; this->y = y; }

    float Vec2f::hypot(const Vec2f& vec) { return std::hypot(vec.x, vec.y); }
    float Vec2f::cross(const Vec2f& a, const Vec2f& b) { return (a.x * b.y) - (a.y * b.x); }
    float Vec2f::dot(const Vec2f& a, const Vec2f& b) { return (a.x * b.x) + (a.y * b.y); }

    Vec2f::Vec2f(const Vec2i& vec) { x = (float)vec.x; y = (float)vec.y; }
    Vec2f::Vec2f(const Vec2d& vec) { x = (float)vec.x; y = (float)vec.y; }
    Vec2f& Vec2f::operator = (const Vec2i& vec) { x = (float)vec.x; y = (float)vec.y; return *this; }
    Vec2f& Vec2f::operator = (const Vec2d& vec) { x = (float)vec.x; y = (float)vec.y; return *this; }

    Vec2f  Vec2f::operator +  (const Vec2f& vec)   const { return Vec2f(x + vec.x, y + vec.y); }
    Vec2f  Vec2f::operator -  (const Vec2f& vec)   const { return Vec2f(x - vec.x, y - vec.y); }
    Vec2f  Vec2f::operator *  (const float scale)  const { return Vec2f(x * scale, y * scale); }
    Vec2f  Vec2f::operator /  (const float scale)  const { zero(scale); return Vec2f(x / scale, y / scale); }
    Vec2f& Vec2f::operator += (const Vec2f& vec)  { x += vec.x; y += vec.y; return *this; }
    Vec2f& Vec2f::operator -= (const Vec2f& vec)  { x -= vec.x; y -= vec.y; return *this; }
    Vec2f& Vec2f::operator *= (const float scale) { x *= scale; y *= scale; return *this; }
    Vec2f& Vec2f::operator /= (const float scale) { zero(scale); x /= scale; y /= scale; return *this; }

    /* Vec2d */

    Vec2d::Vec2d(double x, double y) { this->x = x; this->y = y; }

    double Vec2d::hypot(const Vec2d& vec) { return std::hypot(vec.x, vec.y); }
    double Vec2d::cross(const Vec2d& a, const Vec2d& b) { return (a.x * b.y) - (a.y * b.x); }
    double Vec2d::dot(const Vec2d& a, const Vec2d& b) { return (a.x * b.x) + (a.y * b.y); }

    Vec2d::Vec2d(const Vec2i& vec) { x = (double)vec.x; y = (double)vec.y; }
    Vec2d::Vec2d(const Vec2f& vec) { x = (double)vec.x; y = (double)vec.y; }
    Vec2d& Vec2d::operator = (const Vec2i& vec) { x = (double)vec.x; y = (double)vec.y; return *this; }
    Vec2d& Vec2d::operator = (const Vec2f& vec) { x = (double)vec.x; y = (double)vec.y; return *this; }

    Vec2d  Vec2d::operator +  (const Vec2d& vec)   const { return Vec2d(x + vec.x, y + vec.y); }
    Vec2d  Vec2d::operator -  (const Vec2d& vec)   const { return Vec2d(x - vec.x, y - vec.y); }
    Vec2d  Vec2d::operator *  (const double scale) const { return Vec2d(x * scale, y * scale); }
    Vec2d  Vec2d::operator /  (const double scale) const { zero(scale); return Vec2d(x / scale, y / scale); }
    Vec2d& Vec2d::operator += (const Vec2d& vec)   { x += vec.x; y += vec.y; return *this; }
    Vec2d& Vec2d::operator -= (const Vec2d& vec)   { x -= vec.x; y -= vec.y; return *this; }
    Vec2d& Vec2d::operator *= (const double scale) { x *= scale; y *= scale; return *this; }
    Vec2d& Vec2d::operator /= (const double scale) { zero(scale); x /= scale; y /= scale; return *this; }

    /* Vec3i */

    Vec3i::Vec3i(int x, int y, int z) { this->x = x; this->y = y; this->z = z; }

    Vec3i Vec3i::xpos() { return Vec3i( 1, 0, 0); }
    Vec3i Vec3i::xneg() { return Vec3i(-1, 0, 0); }
    Vec3i Vec3i::ypos() { return Vec3i( 0, 1, 0); }
    Vec3i Vec3i::yneg() { return Vec3i( 0,-1, 0); }
    Vec3i Vec3i::zpos() { return Vec3i( 0, 0, 1); }
    Vec3i Vec3i::zneg() { return Vec3i( 0, 0,-1); }
    double Vec3i::hypot(const Vec3i& vec) { return std::hypot(vec.x, vec.y, vec.z); }


    /* Vec3f */
    
    
    
    /* Vec3d */



}

