
/*
    Camera.cpp
*/

#include "Violet.h"

namespace Vi {

    Vec3d Camera::forward() const {
        return Vec3d();
    }

    Vec3d Camera::up() const {
        return Vec3d();
    }

    Vec3d Camera::right() const {
        return Vec3d();
    }

    Mat4 Camera::view_matrix() const {
        Mat4 translation_matrix_inverse = Mat4::translation_matrix(position * -1.0);
        Mat4 rotation_matrix_inverse = Mat4::rotation_matrix(orientation.complex_conjugate());
        return rotation_matrix_inverse * translation_matrix_inverse;
    }

    Mat4 Camera::projection_matrix(const Vec2i screen_size) const {
        return Mat4();
    }
}

