
/*
    Transform.cpp
*/

#include "Violet.h"

namespace Vi {

    Mat4 Transform::model_matrix() const {
        Mat4 scalar_matrix = Mat4::scalar_matrix(scale);
        Mat4 translation_matrix = Mat4::translation_matrix(position);
        Mat4 rotation_matrix = Mat4::rotation_matrix(orientation);
        return scalar_matrix * translation_matrix * rotation_matrix;
    }

    Mat4 Transform::view_matrix() const {
        Mat4 translation_matrix_inverse = Mat4::translation_matrix(position * -1.0);
        Mat4 rotation_matrix_inverse = Mat4::rotation_matrix(orientation.complex_conjugate());
        return rotation_matrix_inverse * translation_matrix_inverse;
    }

    Mat4 Transform::projection_matrix() const {

    }
}

