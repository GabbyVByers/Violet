
/*
    sprite.cpp
*/

#include "../rendering.h"
#include "../logging.h"

namespace Vi {

    /* Public */

    Sprite::Sprite() {
        Vertex tl = Vertex(Vec3f(0.0f, 0.0f, 0.0f), Color::white(), Vec2f(0.0f, 1.0f));
        Vertex tr = Vertex(Vec3f(1.0f, 0.0f, 0.0f), Color::white(), Vec2f(1.0f, 1.0f));
        Vertex bl = Vertex(Vec3f(0.0f,-1.0f, 0.0f), Color::white(), Vec2f(0.0f, 0.0f));
        Vertex br = Vertex(Vec3f(1.0f,-1.0f, 0.0f), Color::white(), Vec2f(1.0f, 0.0f));
        std::vector<Vertex> verts = { tl, tr, bl, tr, br, bl };
        vertices.insert(vertices.begin(), verts.begin(), verts.end());
    }

    /* Private */

    Mat4 Sprite::model_matrix(const Vec2i& viewport_size) const {
        double aspect_ratio = (double)viewport_size.x / (double)viewport_size.y;
        double sx = 2.0 * ((double)size.x / (double)viewport_size.x);
        double sy = 2.0 * ((double)size.y / (double)viewport_size.y);
        Mat4 scalar_matrix = Mat4(
            sx, 0, 0, 0,
            0, sy, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        );
        double px = (((double)position.x / (double)viewport_size.x) * 2.0) - 1.0;
        double py = (1.0 - (((double)position.y / (double)viewport_size.y) * 2.0));
        Mat4 translation_matrix = Mat4::translation_matrix(Vec3d(px, py, 0.0));
        return translation_matrix * scalar_matrix;
    }
}

