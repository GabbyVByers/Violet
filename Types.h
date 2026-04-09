
#pragma once

#define Vi Vi
namespace Vi {

    /* Vector */

    class Vec2i;
    class Vec2f;
    class Vec2d;

    class Vec3i;
    class Vec3f;
    class Vec3d;

    class Vec2i {
    public:
        int x, y;
    };

    class Vec2f {
    public:
        float x, y;
    };

    class Vec2d {
    public:
        double x, y;

        Vec2d operator + (const Vec2d& other) { return Vec2d(x + other.x, y + other.y); }
        Vec2d operator - (const Vec2d& other) { return Vec2d(x - other.x, y - other.y); }
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

    /* Color */

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

