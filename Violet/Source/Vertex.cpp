
/*
    Vertex.cpp
*/

#include "../Violet.h"

namespace Vi {

    Vertex::Vertex(const Vec3f& pos, const Color& col, const Vec2f& tex) {
        position = pos;
        color = col;
        tex_coord = tex;
    }
}

