
/*
    vector.cpp
*/

#include "../rendering.h"
#include "../logging.h"
#include <iostream>
#include <cmath>

namespace Vi {

    /* Divide by Zero Warning */

    template<typename type>
    static void zero(const type val) {
        if (val == type{}) {
            Log::warning("Vector math operation resulted in division by zero!");
        }
    }
    
    /* Vec2i */

    double Vec2i::length() const {
        return std::hypot(x, y);
    }
    
    Vec2i  Vec2i::operator +  (const Vec2i& vec) const { return Vec2i(x + vec.x, y + vec.y); }
    Vec2i  Vec2i::operator -  (const Vec2i& vec) const { return Vec2i(x - vec.x, y - vec.y); }
    Vec2i  Vec2i::operator *  (const int scale)  const { return Vec2i(x * scale, y * scale); }
    Vec2i  Vec2i::operator /  (const int scale)  const { zero(scale); return Vec2i(x / scale, y / scale); }
    Vec2i& Vec2i::operator += (const Vec2i& vec) { x += vec.x; y += vec.y; return *this; }
    Vec2i& Vec2i::operator -= (const Vec2i& vec) { x -= vec.x; y -= vec.y; return *this; }
    Vec2i& Vec2i::operator *= (const int scale)  { x *= scale; y *= scale; return *this; }
    Vec2i& Vec2i::operator /= (const int scale)  { zero(scale); x /= scale; y /= scale; return *this; }
    
    Vec2i::operator Vec2f() const { return Vec2f((float)x, (float)y); }
    Vec2i::operator Vec2d() const { return Vec2d((double)x, (double)y); }

    /* Vec2f */
    
    float Vec2f::length() const {
        return std::hypot(x, y);
    }

    Vec2f Vec2f::normalized() const {
        float len = length();
        return Vec2f(x / len, y / len);
    }
    
    Vec2f  Vec2f::operator +  (const Vec2f& vec)   const { return Vec2f(x + vec.x, y + vec.y); }
    Vec2f  Vec2f::operator -  (const Vec2f& vec)   const { return Vec2f(x - vec.x, y - vec.y); }
    Vec2f  Vec2f::operator *  (const float scale)  const { return Vec2f(x * scale, y * scale); }
    Vec2f  Vec2f::operator /  (const float scale)  const { zero(scale); return Vec2f(x / scale, y / scale); }
    Vec2f& Vec2f::operator += (const Vec2f& vec)  { x += vec.x; y += vec.y; return *this; }
    Vec2f& Vec2f::operator -= (const Vec2f& vec)  { x -= vec.x; y -= vec.y; return *this; }
    Vec2f& Vec2f::operator *= (const float scale) { x *= scale; y *= scale; return *this; }
    Vec2f& Vec2f::operator /= (const float scale) { zero(scale); x /= scale; y /= scale; return *this; }
    
    Vec2f::operator Vec2i() const { return Vec2i((int)x, (int)y); }
    Vec2f::operator Vec2d() const { return Vec2d((double)x, (double)y); }

    /* Vec2d */

    double Vec2d::length() const {
        return std::hypot(x, y);
    }

    Vec2d Vec2d::normalized() const {
        double len = length();
        return Vec2d(x / len, y / len);
    }
    
    Vec2d  Vec2d::operator +  (const Vec2d& vec)   const { return Vec2d(x + vec.x, y + vec.y); }
    Vec2d  Vec2d::operator -  (const Vec2d& vec)   const { return Vec2d(x - vec.x, y - vec.y); }
    Vec2d  Vec2d::operator *  (const double scale) const { return Vec2d(x * scale, y * scale); }
    Vec2d  Vec2d::operator /  (const double scale) const { zero(scale); return Vec2d(x / scale, y / scale); }
    Vec2d& Vec2d::operator += (const Vec2d& vec)   { x += vec.x; y += vec.y; return *this; }
    Vec2d& Vec2d::operator -= (const Vec2d& vec)   { x -= vec.x; y -= vec.y; return *this; }
    Vec2d& Vec2d::operator *= (const double scale) { x *= scale; y *= scale; return *this; }
    Vec2d& Vec2d::operator /= (const double scale) { zero(scale); x /= scale; y /= scale; return *this; }
    
    Vec2d::operator Vec2i() const { return Vec2i((int)x, (int)y); }
    Vec2d::operator Vec2f() const { return Vec2f((float)x, (float)y); }

    /* Vec3i */

    double Vec3i::length() const {
        return std::hypot(x, y, z);
    }
    
    Vec3i  Vec3i::operator +  (const Vec3i& vec) const { return Vec3i(x + vec.x, y + vec.y, z + vec.z); }
    Vec3i  Vec3i::operator -  (const Vec3i& vec) const { return Vec3i(x - vec.x, y - vec.y, z - vec.z); }
    Vec3i  Vec3i::operator *  (const int scale)  const { return Vec3i(x * scale, y * scale, z * scale); }
    Vec3i  Vec3i::operator /  (const int scale)  const { zero(scale); return Vec3i(x / scale, y / scale, z / scale); }
    Vec3i& Vec3i::operator += (const Vec3i& vec) { x += vec.x; y += vec.y; z += vec.z; return *this; }
    Vec3i& Vec3i::operator -= (const Vec3i& vec) { x -= vec.x; y -= vec.y; z -= vec.z; return *this; }
    Vec3i& Vec3i::operator *= (const int scale)  { x *= scale; y *= scale; z *= scale; return *this; }
    Vec3i& Vec3i::operator /= (const int scale)  { zero(scale); x /= scale; y /= scale; z /= scale; return *this; }
    
    Vec3i::operator Vec3f() const { return Vec3f((float)x, (float)y, (float)z); }
    Vec3i::operator Vec3d() const { return Vec3d((double)x, (double)y, (double)z); }

    /* Vec3f */
    
    float Vec3f::length() const {
        return std::hypot(x, y, z);
    }
    
    Vec3f Vec3f::normalized() const {
        float len = length();
        return Vec3f(x / len, y / len, z / len);
    }
    
    Vec3f  Vec3f::operator +  (const Vec3f& vec)  const { return Vec3f(x + vec.x, y + vec.y, z + vec.z); }
    Vec3f  Vec3f::operator -  (const Vec3f& vec)  const { return Vec3f(x - vec.x, y - vec.y, z - vec.z); }
    Vec3f  Vec3f::operator *  (const float scale) const { return Vec3f(x * scale, y * scale, z * scale); }
    Vec3f  Vec3f::operator /  (const float scale) const { zero(scale); return Vec3f(x / scale, y / scale, z / scale); }
    Vec3f& Vec3f::operator += (const Vec3f& vec)  { x += vec.x; y += vec.y; z += vec.z; return *this; }
    Vec3f& Vec3f::operator -= (const Vec3f& vec)  { x -= vec.x; y -= vec.y; z -= vec.z; return *this; }
    Vec3f& Vec3f::operator *= (const float scale) { x *= scale; y *= scale; z *= scale; return *this; }
    Vec3f& Vec3f::operator /= (const float scale) { zero(scale); x /= scale; y /= scale; z /= scale; return *this; }
    
    Vec3f::operator Vec3i() const { return Vec3i((int)x, (int)y, (int)z); }
    Vec3f::operator Vec3d() const { return Vec3d((double)x, (double)y, (double)z); }
    
    /* Vec3d */

    double Vec3d::length() const {
        return std::hypot(x, y, z);
    }

    Vec3d Vec3d::normalized() const {
        double len = length();
        return Vec3d(x / len, y / len, z / len);
    }
    
    Vec3d Vec3d::rotated_around(const Vec3d& axis, const double theta) const {
        Quat q_rot = Quat::rotation(axis, theta);
        return rotated_using(q_rot);
    }
    
    Vec3d Vec3d::rotated_using(const Quat& q_rot) const {
        Quat q_inv = q_rot.complex_conjugate();
        Quat p = Quat(0.0, x, y, z);
        Quat result = q_rot * p * q_inv;
        return Vec3d(
            result.x,
            result.y,
            result.z
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
    
    Vec3d::operator Vec3i() const { return Vec3i((int)x, (int)y, (int)z); }
    Vec3d::operator Vec3f() const { return Vec3f((float)x, (float)y, (float)z); }

    /* Dot Products */

    int Vec2::dot(const Vec2i& a, const Vec2i& b) {
        return (a.x * b.x) + (a.y * b.y);
    }

    float Vec2::dot(const Vec2f& a, const Vec2f& b) {
        return (a.x * b.x) + (a.y * b.y);
    }
        
    double Vec2::dot(const Vec2d& a, const Vec2d& b) {
        return (a.x * b.x) + (a.y * b.y);
    }
        
    int Vec3::dot(const Vec3i& a, const Vec3i& b) {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    }
        
    float Vec3::dot(const Vec3f& a, const Vec3f& b) {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    }
        
    double Vec3::dot(const Vec3d& a, const Vec3d& b) {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    }
    
    /* Cross Products */
        
    int Vec2::cross(const Vec2i& a, const Vec2i& b) {
        return (a.x * b.y) - (a.y * b.x);
    }
        
    float Vec2::cross(const Vec2f& a, const Vec2f& b) {
        return (a.x * b.y) - (a.y * b.x);
    }
        
    double Vec2::cross(const Vec2d& a, const Vec2d& b) {
        return (a.x * b.y) - (a.y * b.x);
    }
        
    Vec3i Vec3::cross(const Vec3i& a, const Vec3i& b) {
        return Vec3i(
            (a.y * b.z) - (a.z * b.y),
            (a.z * b.x) - (a.x * b.z),
            (a.x * b.y) - (a.y * b.x)
        );
    }
        
    Vec3f Vec3::cross(const Vec3f& a, const Vec3f& b) {
        return Vec3f(
            (a.y * b.z) - (a.z * b.y),
            (a.z * b.x) - (a.x * b.z),
            (a.x * b.y) - (a.y * b.x)
        );
    }

    Vec3d Vec3::cross(const Vec3d& a, const Vec3d& b) {
        return Vec3d(
            (a.y * b.z) - (a.z * b.y),
            (a.z * b.x) - (a.x * b.z),
            (a.x * b.y) - (a.y * b.x)
        );
    }

    /* Angle Between Vectors */

    double Vec2::angle(const Vec2i& a, const Vec2i& b) {
        return std::acos(dot(a, b) / (a.length() * b.length()));
    }
        
    double Vec2::angle(const Vec2f& a, const Vec2f& b) {
        return std::acos(dot(a, b) / (a.length() * b.length()));
    }
        
    double Vec2::angle(const Vec2d& a, const Vec2d& b) {
        return std::acos(dot(a, b) / (a.length() * b.length()));
    }
        
    double Vec3::angle(const Vec3i& a, const Vec3i& b) {
        return std::acos(dot(a, b) / (a.length() * b.length()));
    }
        
    double Vec3::angle(const Vec3f& a, const Vec3f& b) {
        return std::acos(dot(a, b) / (a.length() * b.length()));
    }

    double Vec3::angle(const Vec3d& a, const Vec3d& b) {
        return std::acos(dot(a, b) / (a.length() * b.length()));
    }

    /* Basis Directions */

    Vec2i Vec2::xpos() { return Vec2i( 1, 0); }
    Vec2i Vec2::xneg() { return Vec2i(-1, 0); }
    Vec2i Vec2::ypos() { return Vec2i( 0, 1); }
    Vec2i Vec2::yneg() { return Vec2i( 0,-1); }

    Vec3i Vec3::xpos() { return Vec3i( 1, 0, 0); }
    Vec3i Vec3::xneg() { return Vec3i(-1, 0, 0); }
    Vec3i Vec3::ypos() { return Vec3i( 0, 1, 0); }
    Vec3i Vec3::yneg() { return Vec3i( 0,-1, 0); }
    Vec3i Vec3::zpos() { return Vec3i( 0, 0, 1); }
    Vec3i Vec3::zneg() { return Vec3i( 0, 0,-1); }
}

