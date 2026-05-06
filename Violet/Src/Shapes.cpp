
/*
    Shapes.cpp
*/

#include "../Shapes.h"
#include <numbers>

namespace Vi {

    Sphere::Sphere(int divisions) {

        std::vector<Vec3d> points;
        double stride = 1.0 / ((double)divisions + 1.0);
        for (int i = 0; i < (divisions + 1); i++) {
            for (int j = 0; j < (divisions + 1); j++) {
                Vec3d tl = Vec3d(-0.5 + (i * stride), -0.5 + (j * stride), -0.5);
                Vec3d tr = Vec3d(tl.x + stride, tl.y, -0.5);
                Vec3d bl = Vec3d(tl.x, tl.y + stride, -0.5);
                Vec3d br = Vec3d(tl.x + stride, tl.y + stride, -0.5);
                std::vector<Vec3d> pts = { tl, tr, bl, tr, br, bl };
                points.insert(points.end(), pts.begin(), pts.end());
            }
        }

        double half_pi = std::numbers::pi * 0.5;
        std::vector<Quat> rotations = {
            Quat::rotation(Vec3d::ypos(), half_pi * 0),
            Quat::rotation(Vec3d::ypos(), half_pi * 1),
            Quat::rotation(Vec3d::ypos(), half_pi * 2),
            Quat::rotation(Vec3d::ypos(), half_pi * 3),
            Quat::rotation(Vec3d::xpos(), half_pi * 1),
            Quat::rotation(Vec3d::xpos(), half_pi * -1)
        };

        for (const Quat& rot : rotations) {
            for (const Vec3d& point : points) {
                Vec3d p = Vec3d::rotate(point.normalized(), rot); // remove .normalized to make a cube!
                Vertex vert = {
                    .position = static_cast<Vec3f>(p),
                    .color = Color::random(),
                    .tex_coord = Vec2f((float)p.x, (float)p.y) // surely wrong
                };
                vertices.push_back(vert);
            }
        }

        Vi::Log::info("Stop!");
    }

    Vec2f Sphere::screen_position() const {
        return Vec2f{};
    }

    float Sphere::apparent_radius() const {
        return float{};
    }
}

