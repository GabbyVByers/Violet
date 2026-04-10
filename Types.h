
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
        Vec2i() = default;
        Vec2i(int, int);
        explicit Vec2i(const Vec2f&);
        explicit Vec2i(const Vec2d&);
        Vec2i& operator = (const Vec2f&);
        Vec2i& operator = (const Vec2d&);
        int x = 0;
        int y = 0;
        
        static Vec2i xpos();
        static Vec2i xneg();
        static Vec2i ypos();
        static Vec2i yneg();
        double hypot() const;
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
    };

    /* Vec2f */

    class Vec2f {
    public:
        Vec2f() = default;
        Vec2f(float, float);
        explicit Vec2f(const Vec2i&);
        explicit Vec2f(const Vec2d&);
        Vec2f& operator = (const Vec2i&);
        Vec2f& operator = (const Vec2d&);
        float x = 0.0f;
        float y = 0.0f;

        static Vec2f xpos();
        static Vec2f xneg();
        static Vec2f ypos();
        static Vec2f yneg();
        float hypot() const;
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
    };

    /* Vec2d */

    class Vec2d {
    public:
        Vec2d() = default;
        Vec2d(double, double);
        explicit Vec2d(const Vec2i&);
        explicit Vec2d(const Vec2f&);
        Vec2d& operator = (const Vec2i&);
        Vec2d& operator = (const Vec2f&);
        double x = 0.0;
        double y = 0.0;

        static Vec2d xpos();
        static Vec2d xneg();
        static Vec2d ypos();
        static Vec2d yneg();
        double hypot() const;
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
    };

    /* Vec3i */

    class Vec3i {
    public:
        Vec3i() = default;
        Vec3i(int, int, int);
        explicit Vec3i(const Vec3f&);
        explicit Vec3i(const Vec3d&);
        Vec3i& operator = (const Vec3f&);
        Vec3i& operator = (const Vec3d&);
        int x = 0;
        int y = 0;
        int z = 0;

        static Vec3i xpos();
        static Vec3i xneg();
        static Vec3i ypos();
        static Vec3i yneg();
        static Vec3i zpos();
        static Vec3i zneg();
        double hypot() const;
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
    };

    /* Vec3f */

    class Vec3f {
    public:
        Vec3f() = default;
        Vec3f(float, float, float);
        explicit Vec3f(const Vec3i&);
        explicit Vec3f(const Vec3d&);
        Vec3f& operator = (const Vec3i&);
        Vec3f& operator = (const Vec3d&);
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        static Vec3f xpos();
        static Vec3f xneg();
        static Vec3f ypos();
        static Vec3f yneg();
        static Vec3f zpos();
        static Vec3f zneg();
        float hypot() const;
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
    };

    /* Vec3d */

    class Vec3d {
    public:
        Vec3d() = default;
        Vec3d(double, double, double);
        explicit Vec3d(const Vec3i&);
        explicit Vec3d(const Vec3f&);
        Vec3d& operator = (const Vec3i&);
        Vec3d& operator = (const Vec3f&);
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;

        static Vec3d xpos();
        static Vec3d xneg();
        static Vec3d ypos();
        static Vec3d yneg();
        static Vec3d zpos();
        static Vec3d zneg();
        double hypot() const;
        static double dot(const Vec3d&, const Vec3d&);
        static Vec3d cross(const Vec3d&, const Vec3d&);

        Vec3d  operator +  (const Vec3d&) const;
        Vec3d  operator -  (const Vec3d&) const;
        Vec3d  operator *  (const double) const;
        Vec3d  operator /  (const double) const;
        Vec3d& operator += (const Vec3d&);
        Vec3d& operator -= (const Vec3d&);
        Vec3d& operator *= (const double);
        Vec3d& operator /= (const double);
    };

    /* Quaternion, Matrix */

    class Quat {
    public:
        Quat() = default;
        Quat(double, double, double, double);
        double w = 1.0, x = 0.0, y = 0.0, z = 0.0;
        Quat normalized() const;
        Quat complex_conjugate() const;
        Quat operator * (const Quat&) const;
    };

    class Mat4 {
    public:
        Mat4();
        static Mat4 scalar_matrix(const double);
        static Mat4 translation_matrix(const Vec3d&);
        static Mat4 rotation_matrix(const Quat&);
        Mat4 operator * (const Mat4&) const;
    private:
        friend Mat4f;
        Mat4(
            double, double, double, double,
            double, double, double, double,
            double, double, double, double,
            double, double, double, double
        );
        double data[4][4];
    };

    class Mat4f {
    public:
        ~Mat4f() = default;
        explicit Mat4f(const Mat4&);
        float* ptr() const;
    private:
        Mat4f() = default;
        Mat4f(const Mat4f&) = default;
        Mat4f(Mat4f&&) noexcept = default;
        Mat4f& operator = (const Mat4f&) = default;
        Mat4f& operator = (Mat4f&&) noexcept = default;
        float data[4][4];
    };
}

