
/*
    Shapes.h
*/

#include "Rendering.h"

#define Vi Vi
namespace Vi {

    class Cube : public Mesh {
    public:
        Cube(int = 0);
    };

    class Sphere : public Mesh {
    public:
        Sphere(int = 10);
        Vec2f screen_position() const;
        float apparent_radius() const;
    };

    class Arrow : public Mesh {
    public:
        Arrow();
    };
}

