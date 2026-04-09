
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
    class Quat;
    class Mat4;
    class Mat4f;

    /* Vec2i */

    class Vec2i {
    public:
        int x, y;
        Vec2i(int = 0, int = 0);
        Vec2i(const Vec2i&) = default;
        Vec2i(Vec2i&&) noexcept = default;
        Vec2i& operator = (const Vec2i&) = default;
        Vec2i& operator = (Vec2i&&) noexcept = default;
        ~Vec2i() = default;
        
        static double hypot(const Vec2i&);
        static int    cross(const Vec2i&, const Vec2i&);
        static int    dot(const Vec2i&, const Vec2i&);
        
        explicit Vec2i(const Vec2f&);
        explicit Vec2i(const Vec2d&);
        Vec2i& operator = (const Vec2f&);
        Vec2i& operator = (const Vec2d&);
        
        Vec2i  operator +  (const Vec2i&) const;
        Vec2i  operator -  (const Vec2i&) const;
        Vec2i  operator *  (const int) const;
        Vec2i  operator /  (const int) const;
        Vec2i& operator += (const Vec2i&);
        Vec2i& operator -= (const Vec2i&);
        Vec2i& operator *= (const int);
        Vec2i& operator /= (const int);
    };

    /* Vec2f */

    class Vec2f {
    public:
        float x, y;
        Vec2f(float = 0.0f, float = 0.0f);
        Vec2f(const Vec2f&) = default;
        Vec2f(Vec2f&&) noexcept = default;
        Vec2f& operator = (const Vec2f&) = default;
        Vec2f& operator = (Vec2f&&) noexcept = default;
        ~Vec2f() = default;

        static float hypot(const Vec2f&);
        static float cross(const Vec2f&, const Vec2f&);
        static float dot(const Vec2f&, const Vec2f&);

        explicit Vec2f(const Vec2i&);
        explicit Vec2f(const Vec2d&);
        Vec2f& operator = (const Vec2i&);
        Vec2f& operator = (const Vec2d&);

        Vec2f  operator +  (const Vec2f&) const;
        Vec2f  operator -  (const Vec2f&) const;
        Vec2f  operator *  (const float) const;
        Vec2f  operator /  (const float) const;
        Vec2f& operator += (const Vec2f&);
        Vec2f& operator -= (const Vec2f&);
        Vec2f& operator *= (const float);
        Vec2f& operator /= (const float);
    };

    /* Vec2d */

    class Vec2d {
    public:
        double x, y;
        Vec2d(double = 0.0, double = 0.0);
        Vec2d(const Vec2d&) = default;
        Vec2d(Vec2d&&) noexcept = default;
        Vec2d& operator = (const Vec2d&) = default;
        Vec2d& operator = (Vec2d&&) noexcept = default;
        ~Vec2d() = default;

        /* todo xpos() */
        static double hypot(const Vec2d&);
        static double cross(const Vec2d&, const Vec2d&);
        static double dot(const Vec2d&, const Vec2d&);

        explicit Vec2d(const Vec2i&);
        explicit Vec2d(const Vec2f&);
        Vec2d& operator = (const Vec2i&);
        Vec2d& operator = (const Vec2f&);

        Vec2d  operator +  (const Vec2d&) const;
        Vec2d  operator -  (const Vec2d&) const;
        Vec2d  operator *  (const double) const;
        Vec2d  operator /  (const double) const;
        Vec2d& operator += (const Vec2d&);
        Vec2d& operator -= (const Vec2d&);
        Vec2d& operator *= (const double);
        Vec2d& operator /= (const double);
    };

    /* Vec3i */

    class Vec3i {
    public:
        int x, y, z;
        Vec3i(int = 0, int = 0, int = 0);
        Vec3i(const Vec3i&) = default;
        Vec3i(Vec3i&&) noexcept = default;
        Vec3i& operator = (const Vec3i&) = default;
        Vec3i& operator = (Vec3i&&) noexcept = default;
        ~Vec3i() = default;

        static Vec3i xpos();
        static Vec3i xneg();
        static Vec3i ypos();
        static Vec3i yneg();
        static Vec3i zpos();
        static Vec3i zneg();
        static double hypot(const Vec3i&);
        static Vec3i  cross(const Vec3i&, const Vec3i&);
        static double dot(const Vec3i&, const Vec3i&);

        explicit Vec3i(const Vec3f&);
        explicit Vec3i(const Vec3d&);
        Vec3i& operator = (const Vec3f&);
        Vec3i& operator = (const Vec3d&);

        Vec3i  operator +  (const Vec3i&) const;
        Vec3i  operator -  (const Vec3i&) const;
        Vec3i  operator *  (const int) const;
        Vec3i  operator /  (const int) const;
        Vec3i& operator += (const Vec3i&);
        Vec3i& operator -= (const Vec3i&);
        Vec3i& operator *= (const int);
        Vec3i& operator /= (const int);
    };

    /* Vec3f */

    class Vec3f {
    public:
        float x, y, z;
    };

    /* Vec3d */

    class Vec3d {
    public:
        double x, y, z;
    };

    /* Color, Quat, Mat, Mat4 */

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
}

