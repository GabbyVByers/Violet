
/*
    Camera.cpp
*/

#include "Violet.h"

namespace Vi {

    Camera::Camera() {
        far = 100.0f;
        near = 0.1f;
        fov = 70.0f;
        transform = {
            .scale = 1.0,
            .position = Vec3d(),
            .orientation = Quat()
        };
    }

    Camera::Camera(double nr, double fr, double fv) {
        near = nr;
        far = fr;
        fov = fv;
        transform = {
            .scale = 1.0,
            .position = Vec3d(),
            .orientation = Quat()
        };
    }

    Vec3d Camera::forward() const {

    }

    Vec3d Camera::up() const {

    }

    Vec3d Camera::right() const {

    }

    Mat4 Camera::view_matrix() const {

    }

    Mat4 Camera::projection_matrix() const {

    }
}

