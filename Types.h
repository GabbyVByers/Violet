
/*
    Types.h
*/

#pragma once

#define Vi Vi
namespace Vi {

    class Vec2i;
    class Vec2f;
    class Vec2d;
    class Vec3i;
    class Vec3f;
    class Vec3d;

    class Color;
    class Vertex;
    class Quat;
    class Mat4;
    class Mat4f;

    /* Vector */

    class Vec2i {
    public:
        int x, y;
        Vec2i();
        Vec2i(int, int);
        Vec2i(const Vec2i&) = default;
        Vec2i(Vec2i&&) noexcept = default;
        Vec2i& operator = (const Vec2i&) = default;
        Vec2i& operator = (Vec2i&&) noexcept = default;
        ~Vec2i() = default;
        
        static double hypot(const Vec2i&);
        static int    cross(const Vec2i&, const Vec2i&);
        static int    dot(const Vec2i&, const Vec2i&);
        
        Vec2i(const Vec2f&);
        Vec2i(const Vec2d&);
        Vec2i& operator = (const Vec2f&);
        Vec2i& operator = (const Vec2d&);
        
        Vec2i  operator +  (const Vec2i&);
        Vec2i  operator -  (const Vec2i&);
        Vec2i  operator *  (const int);
        Vec2i  operator /  (const int);
        Vec2i& operator += (const Vec2i&);
        Vec2i& operator -= (const Vec2i&);
        Vec2i& operator *= (const int);
        Vec2i& operator /= (const int);
    };

    class Vec2f {
    public:
        float x, y;
        Vec2f();
        Vec2f(float, float);
    };

    class Vec2d {
    public:
        double x, y;
        Vec2d();
        Vec2d(double, double);

        Vec2d  operator + (const Vec2d& other) { return Vec2d(x + other.x, y + other.y); }
        Vec2d  operator - (const Vec2d& other) { return Vec2d(x - other.x, y - other.y); }
        Vec2d& operator = (const Vec2d& other) { x = other.x; y = other.y; return *this; }
    };

    class Vec3i {
    public:
        int x, y, z;
    };

    class Vec3f {
    public:
        float x, y, z;
    };

    class Vec3d {
    public:
        double x, y, z;
    };

    /* Color, Vertex, Transform, Quaternion, Matrix */

    class Quat {
    public:
        double w, x, y, z;
    };

    class Mat4 {
    public:
        double data[4][4];
    };

    class Mat4f {
    public:
        float data[4][4];
    };

    class Color {
    public:
        float r, g, b, a;

        static Color white()  { return Color(1.0f, 1.0f, 1.0f, 1.0f); }
        static Color black()  { return Color(0.0f, 0.0f, 0.0f, 1.0f); }
        static Color red()    { return Color(1.0f, 0.0f, 0.0f, 1.0f); }
        static Color green()  { return Color(0.0f, 1.0f, 0.0f, 1.0f); }
        static Color blue()   { return Color(0.0f, 0.0f, 1.0f, 1.0f); }
        static Color cyan()   { return Color(0.0f, 1.0f, 1.0f, 1.0f); }
        static Color purple() { return Color(1.0f, 0.0f, 1.0f, 1.0f); }
        static Color yellow() { return Color(1.0f, 1.0f, 0.0f, 1.0f); }
    };
}

