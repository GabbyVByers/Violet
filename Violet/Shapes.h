
/*
    Shapes.h
*/

#include "Rendering.h"

#define Vi Vi
namespace Vi {

    class Sphere : public Mesh {
    public:
        Sphere(int = 10);
        Vec2f screen_position() const;
        float apparent_radius() const;
    };
}

