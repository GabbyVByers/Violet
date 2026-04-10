
/*
    Vector.cpp
*/

#include "Logger.h"
#include "Types.h"
#include <iostream>
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
    Vec2i::Vec2i(const Vec2f& vec) { x = (int)vec.x; y = (int)vec.y; }
    Vec2i::Vec2i(const Vec2d& vec) { x = (int)vec.x; y = (int)vec.y; }
    Vec2i& Vec2i::operator = (const Vec2f& vec) { x = (int)vec.x; y = (int)vec.y; return *this; }
    Vec2i& Vec2i::operator = (const Vec2d& vec) { x = (int)vec.x; y = (int)vec.y; return *this; }

    Vec2i Vec2i::xpos() { return Vec2i( 1, 0); }
    Vec2i Vec2i::xneg() { return Vec2i(-1, 0); }
    Vec2i Vec2i::ypos() { return Vec2i( 0, 1); }
    Vec2i Vec2i::yneg() { return Vec2i( 0,-1); }
    double Vec2i::hypot() const { return std::hypot(x, y); }
    int Vec2i::dot(const Vec2i& a, const Vec2i& b) { return (a.x * b.x) + (a.y * b.y); }
    int Vec2i::cross(const Vec2i& a, const Vec2i& b) { return (a.x * b.y) - (a.y * b.x); }

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
    Vec2f::Vec2f(const Vec2i& vec) { x = (float)vec.x; y = (float)vec.y; }
    Vec2f::Vec2f(const Vec2d& vec) { x = (float)vec.x; y = (float)vec.y; }
    Vec2f& Vec2f::operator = (const Vec2i& vec) { x = (float)vec.x; y = (float)vec.y; return *this; }
    Vec2f& Vec2f::operator = (const Vec2d& vec) { x = (float)vec.x; y = (float)vec.y; return *this; }

    Vec2f Vec2f::xpos() { return Vec2f( 1.0f, 0.0f); }
    Vec2f Vec2f::xneg() { return Vec2f(-1.0f, 0.0f); }
    Vec2f Vec2f::ypos() { return Vec2f( 0.0f, 1.0f); }
    Vec2f Vec2f::yneg() { return Vec2f( 0.0f,-1.0f); }
    float Vec2f::hypot() const { return std::hypot(x, y); }
    float Vec2f::dot(const Vec2f& a, const Vec2f& b) { return (a.x * b.x) + (a.y * b.y); }
    float Vec2f::cross(const Vec2f& a, const Vec2f& b) { return (a.x * b.y) - (a.y * b.x); }

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
    Vec2d::Vec2d(const Vec2i& vec) { x = (double)vec.x; y = (double)vec.y; }
    Vec2d::Vec2d(const Vec2f& vec) { x = (double)vec.x; y = (double)vec.y; }
    Vec2d& Vec2d::operator = (const Vec2i& vec) { x = (double)vec.x; y = (double)vec.y; return *this; }
    Vec2d& Vec2d::operator = (const Vec2f& vec) { x = (double)vec.x; y = (double)vec.y; return *this; }

    Vec2d Vec2d::xpos() { return Vec2d( 1.0, 0.0); }
    Vec2d Vec2d::xneg() { return Vec2d(-1.0, 0.0); }
    Vec2d Vec2d::ypos() { return Vec2d( 0.0, 1.0); }
    Vec2d Vec2d::yneg() { return Vec2d( 0.0,-1.0); }
    double Vec2d::hypot() const { return std::hypot(x, y); }
    double Vec2d::dot(const Vec2d& a, const Vec2d& b) { return (a.x * b.x) + (a.y * b.y); }
    double Vec2d::cross(const Vec2d& a, const Vec2d& b) { return (a.x * b.y) - (a.y * b.x); }

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
    Vec3i::Vec3i(const Vec3f& vec) { x = (int)vec.x; y = (int)vec.y; z = (int)vec.z; }
    Vec3i::Vec3i(const Vec3d& vec) { x = (int)vec.x; y = (int)vec.y; z = (int)vec.z; }
    Vec3i& Vec3i::operator = (const Vec3f& vec) { x = (int)vec.x; y = (int)vec.y; z = (int)vec.z; return *this; }
    Vec3i& Vec3i::operator = (const Vec3d& vec) { x = (int)vec.x; y = (int)vec.y; z = (int)vec.z; return *this; }

    Vec3i Vec3i::xpos() { return Vec3i( 1, 0, 0); }
    Vec3i Vec3i::xneg() { return Vec3i(-1, 0, 0); }
    Vec3i Vec3i::ypos() { return Vec3i( 0, 1, 0); }
    Vec3i Vec3i::yneg() { return Vec3i( 0,-1, 0); }
    Vec3i Vec3i::zpos() { return Vec3i( 0, 0, 1); }
    Vec3i Vec3i::zneg() { return Vec3i( 0, 0,-1); }
    double Vec3i::hypot() const { return std::hypot(x, y, z); }
    int Vec3i::dot(const Vec3i& a, const Vec3i& b) { return (a.x * b.x) + (a.y * b.y) + (a.z * b.z); }
    Vec3i Vec3i::cross(const Vec3i& a, const Vec3i& b) {
        return Vec3i(
            (a.y * b.z) - (a.z * b.y),
            (a.z * b.x) - (a.x * b.z),
            (a.x * b.y) - (a.y * b.x)
        );
    }

    Vec3i  Vec3i::operator +  (const Vec3i& vec) const { return Vec3i(x + vec.x, y + vec.y, z + vec.z); }
    Vec3i  Vec3i::operator -  (const Vec3i& vec) const { return Vec3i(x - vec.x, y - vec.y, z - vec.z); }
    Vec3i  Vec3i::operator *  (const int scale)  const { return Vec3i(x * scale, y * scale, z * scale); }
    Vec3i  Vec3i::operator /  (const int scale)  const { zero(scale); return Vec3i(x / scale, y / scale, z / scale); }
    Vec3i& Vec3i::operator += (const Vec3i& vec) { x += vec.x; y += vec.y; z += vec.z; return *this; }
    Vec3i& Vec3i::operator -= (const Vec3i& vec) { x -= vec.x; y -= vec.y; z -= vec.z; return *this; }
    Vec3i& Vec3i::operator *= (const int scale)  { x *= scale; y *= scale; z *= scale; return *this; }
    Vec3i& Vec3i::operator /= (const int scale)  { zero(scale); x /= scale; y /= scale; z /= scale; return *this; }

    /* Vec3f */
    
    Vec3f::Vec3f(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }
    Vec3f::Vec3f(const Vec3i& vec) { x = (float)vec.x; y = (float)vec.y; z = (float)vec.z; }
    Vec3f::Vec3f(const Vec3d& vec) { x = (float)vec.x; y = (float)vec.y; z = (float)vec.z; }
    Vec3f& Vec3f::operator = (const Vec3i& vec) { x = (float)vec.x; y = (float)vec.y; z = (float)vec.z; return *this; }
    Vec3f& Vec3f::operator = (const Vec3d& vec) { x = (float)vec.x; y = (float)vec.y; z = (float)vec.z; return *this; }

    Vec3f Vec3f::xpos() { return Vec3f( 1.0f, 0.0f, 0.0f); }
    Vec3f Vec3f::xneg() { return Vec3f(-1.0f, 0.0f, 0.0f); }
    Vec3f Vec3f::ypos() { return Vec3f( 0.0f, 1.0f, 0.0f); }
    Vec3f Vec3f::yneg() { return Vec3f( 0.0f,-1.0f, 0.0f); }
    Vec3f Vec3f::zpos() { return Vec3f( 0.0f, 0.0f, 1.0f); }
    Vec3f Vec3f::zneg() { return Vec3f( 0.0f, 0.0f,-1.0f); }
    float Vec3f::hypot() const { return std::hypot(x, y, z); }
    float Vec3f::dot(const Vec3f& a, const Vec3f& b) { return (a.x * b.x) + (a.y * b.y) + (a.z * b.z); }
    Vec3f Vec3f::cross(const Vec3f& a, const Vec3f& b) {
        return Vec3f(
            (a.y * b.z) - (a.z * b.y),
            (a.z * b.x) - (a.x * b.z),
            (a.x * b.y) - (a.y * b.x)
        );
    }

    Vec3f  Vec3f::operator +  (const Vec3f& vec)  const { return Vec3f(x + vec.x, y + vec.y, z + vec.z); }
    Vec3f  Vec3f::operator -  (const Vec3f& vec)  const { return Vec3f(x - vec.x, y - vec.y, z - vec.z); }
    Vec3f  Vec3f::operator *  (const float scale) const { return Vec3f(x * scale, y * scale, z * scale); }
    Vec3f  Vec3f::operator /  (const float scale) const { zero(scale); return Vec3f(x / scale, y / scale, z / scale); }
    Vec3f& Vec3f::operator += (const Vec3f& vec)  { x += vec.x; y += vec.y; z += vec.z; return *this; }
    Vec3f& Vec3f::operator -= (const Vec3f& vec)  { x -= vec.x; y -= vec.y; z -= vec.z; return *this; }
    Vec3f& Vec3f::operator *= (const float scale) { x *= scale; y *= scale; z *= scale; return *this; }
    Vec3f& Vec3f::operator /= (const float scale) { zero(scale); x /= scale; y /= scale; z /= scale; return *this; }
    
    /* Vec3d */

    Vec3d::Vec3d(double x, double y, double z) { this->x = x; this->y = y; this->z = z; }
    Vec3d::Vec3d(const Vec3i& vec) { x = (double)vec.x; y = (double)vec.y; z = (double)vec.z; }
    Vec3d::Vec3d(const Vec3f& vec) { x = (double)vec.x; y = (double)vec.y; z = (double)vec.z; }
    Vec3d& Vec3d::operator = (const Vec3i& vec) { x = (double)vec.x; y = (double)vec.y; z = (double)vec.z; return *this; }
    Vec3d& Vec3d::operator = (const Vec3f& vec) { x = (double)vec.x; y = (double)vec.y; z = (double)vec.z; return *this; }

    Vec3d Vec3d::xpos() { return Vec3d( 1.0, 0.0, 0.0); }
    Vec3d Vec3d::xneg() { return Vec3d(-1.0, 0.0, 0.0); }
    Vec3d Vec3d::ypos() { return Vec3d( 0.0, 1.0, 0.0); }
    Vec3d Vec3d::yneg() { return Vec3d( 0.0,-1.0, 0.0); }
    Vec3d Vec3d::zpos() { return Vec3d( 0.0, 0.0, 1.0); }
    Vec3d Vec3d::zneg() { return Vec3d( 0.0, 0.0,-1.0); }
    double Vec3d::hypot() const { return std::hypot(x, y, z); }
    double Vec3d::dot(const Vec3d& a, const Vec3d& b) { return (a.x * b.x) + (a.y * b.y) + (a.z * b.z); }
    Vec3d  Vec3d::cross(const Vec3d& a, const Vec3d& b) {
        return Vec3d(
            (a.y * b.z) - (a.z * b.y),
            (a.z * b.x) - (a.x * b.z),
            (a.x * b.y) - (a.y * b.x)
        );
    }

    Vec3d  Vec3d::operator +  (const Vec3d& vec)   const { return Vec3d(x + vec.x, y + vec.y, z + vec.z); }
    Vec3d  Vec3d::operator -  (const Vec3d& vec)   const { return Vec3d(x - vec.x, y - vec.y, z - vec.z); }
    Vec3d  Vec3d::operator *  (const double scale) const { return Vec3d(x * scale, y * scale, z * scale); }
    Vec3d  Vec3d::operator /  (const double scale) const { zero(scale); return Vec3d(x / scale, y / scale, z / scale); }
    Vec3d& Vec3d::operator += (const Vec3d& vec)   { x += vec.x; y += vec.y; z += vec.z; return *this; }
    Vec3d& Vec3d::operator -= (const Vec3d& vec)   { x -= vec.x; y -= vec.y; z -= vec.z; return *this; }
    Vec3d& Vec3d::operator *= (const double scale) { x *= scale; y *= scale; z *= scale; return *this; }
    Vec3d& Vec3d::operator /= (const double scale) { zero(scale); x /= scale; y /= scale; z /= scale; return *this; }
}

