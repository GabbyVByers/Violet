
/*
    Math.h
*/

#pragma once

#define Vi Vi
namespace Vi {

    /* Forward Class Declarations */

    class Vec2i;
    class Vec2f;
    class Vec2d;
    class Vec3i;
    class Vec3f;
    class Vec3d;
    class Quat;
    class Mat4;
    class Mat4f;

    /* Vector of Two Integers */

    class Vec2i {
    public:
        int x{};
        int y{};
        double length() const;
        static Vec2i xpos();
        static Vec2i xneg();
        static Vec2i ypos();
        static Vec2i yneg();
        static int dot(const Vec2i&, const Vec2i&);
        static int cross(const Vec2i&, const Vec2i&);
        Vec2i  operator +  (const Vec2i&) const;
        Vec2i  operator -  (const Vec2i&) const;
        Vec2i  operator *  (const int) const;
        Vec2i  operator /  (const int) const;
        Vec2i& operator += (const Vec2i&);
        Vec2i& operator -= (const Vec2i&);
        Vec2i& operator *= (const int);
        Vec2i& operator /= (const int);
        explicit operator Vec2f() const;
        explicit operator Vec2d() const;
    };

    /* Vector of Two Floats */

    class Vec2f {
    public:
        float x{};
        float y{};
        float length() const;
        Vec2f normalized() const;
        static Vec2f xpos();
        static Vec2f xneg();
        static Vec2f ypos();
        static Vec2f yneg();
        static float dot(const Vec2f&, const Vec2f&);
        static float cross(const Vec2f&, const Vec2f&);
        Vec2f  operator +  (const Vec2f&) const;
        Vec2f  operator -  (const Vec2f&) const;
        Vec2f  operator *  (const float) const;
        Vec2f  operator /  (const float) const;
        Vec2f& operator += (const Vec2f&);
        Vec2f& operator -= (const Vec2f&);
        Vec2f& operator *= (const float);
        Vec2f& operator /= (const float);
        explicit operator Vec2i() const;
        explicit operator Vec2d() const;
    };

    /* Vector of Two Doubles */

    class Vec2d {
    public:
        double x{};
        double y{};
        double length() const;
        Vec2d normalized() const;
        static Vec2d xpos();
        static Vec2d xneg();
        static Vec2d ypos();
        static Vec2d yneg();
        static double dot(const Vec2d&, const Vec2d&);
        static double cross(const Vec2d&, const Vec2d&);
        Vec2d  operator +  (const Vec2d&) const;
        Vec2d  operator -  (const Vec2d&) const;
        Vec2d  operator *  (const double) const;
        Vec2d  operator /  (const double) const;
        Vec2d& operator += (const Vec2d&);
        Vec2d& operator -= (const Vec2d&);
        Vec2d& operator *= (const double);
        Vec2d& operator /= (const double);
        explicit operator Vec2i() const;
        explicit operator Vec2f() const;
    };

    /* Vector of Three Integers */

    class Vec3i {
    public:
        int x{};
        int y{};
        int z{};
        double length() const;
        static Vec3i xpos();
        static Vec3i xneg();
        static Vec3i ypos();
        static Vec3i yneg();
        static Vec3i zpos();
        static Vec3i zneg();
        static int dot(const Vec3i&, const Vec3i&);
        static Vec3i cross(const Vec3i&, const Vec3i&);
        Vec3i  operator +  (const Vec3i&) const;
        Vec3i  operator -  (const Vec3i&) const;
        Vec3i  operator *  (const int) const;
        Vec3i  operator /  (const int) const;
        Vec3i& operator += (const Vec3i&);
        Vec3i& operator -= (const Vec3i&);
        Vec3i& operator *= (const int);
        Vec3i& operator /= (const int);
        explicit operator Vec3f() const;
        explicit operator Vec3d() const;
    };

    /* Vector of Three Floats */

    class Vec3f {
    public:
        float x{};
        float y{};
        float z{};
        float length() const;
        Vec3f normalized() const;
        static Vec3f xpos();
        static Vec3f xneg();
        static Vec3f ypos();
        static Vec3f yneg();
        static Vec3f zpos();
        static Vec3f zneg();
        static float dot(const Vec3f&, const Vec3f&);
        static Vec3f cross(const Vec3f&, const Vec3f&);
        Vec3f  operator +  (const Vec3f&) const;
        Vec3f  operator -  (const Vec3f&) const;
        Vec3f  operator *  (const float) const;
        Vec3f  operator /  (const float) const;
        Vec3f& operator += (const Vec3f&);
        Vec3f& operator -= (const Vec3f&);
        Vec3f& operator *= (const float);
        Vec3f& operator /= (const float);
        explicit operator Vec3i() const;
        explicit operator Vec3d() const;
    };

    /* Vector of Three Doubles */

    class Vec3d {
    public:
        double x{};
        double y{};
        double z{};
        double length() const;
        Vec3d normalized() const;
        static Vec3d xpos();
        static Vec3d xneg();
        static Vec3d ypos();
        static Vec3d yneg();
        static Vec3d zpos();
        static Vec3d zneg();
        static double dot(const Vec3d&, const Vec3d&);
        static Vec3d cross(const Vec3d&, const Vec3d&);
        static Vec3d rotate(const Vec3d&, const Vec3d&, double);
        static Vec3d rotate(const Vec3d&, const Quat&);
        static double angle_between(const Vec3d&, const Vec3d&);
        Vec3d  operator +  (const Vec3d&) const;
        Vec3d  operator -  (const Vec3d&) const;
        Vec3d  operator *  (const double) const;
        Vec3d  operator /  (const double) const;
        Vec3d& operator += (const Vec3d&);
        Vec3d& operator -= (const Vec3d&);
        Vec3d& operator *= (const double);
        Vec3d& operator /= (const double);
        explicit operator Vec3i() const;
        explicit operator Vec3f() const;
    };

    /* Quaternions */

    class Quat {
    public:
        double w{ 1.0 };
        double x{};
        double y{};
        double z{};
        Quat normalized() const;
        Quat complex_conjugate() const;
        static Quat rotation(const Vec3d&, const double);
        Quat operator * (const Quat&) const;
    };

    /* 4x4 Matrices */

    class Mat4 {
    public:
        Mat4();
        Mat4(
            double, double, double, double,
            double, double, double, double,
            double, double, double, double,
            double, double, double, double
        );
        static Mat4 scalar_matrix(const double);
        static Mat4 translation_matrix(const Vec3d&);
        static Mat4 rotation_matrix(const Quat&);
        Mat4 operator * (const Mat4&) const;
        explicit operator Mat4f() const;
    private:
        double data[4][4]{};
    };

    class Mat4f {
    public:
        Mat4f();
        float* ptr() const;
    private:
        friend Mat4;
        float data[4][4]{};
    };
}

