
/*
    mesh.cpp
*/

#include "../rendering.h"
#include "../logging.h"
#include <fstream>
#include <sstream>

namespace Vi {

    /* Public */

    void Mesh::paint(const Color& color) {
        for (Vertex& vertex : vertices) {
            vertex.color = color;
        }
    }

    /* Private */

    Mat4 Mesh::model_matrix() const {
        Mat4 scalar_matrix = Mat4::scalar_matrix(scale);
        Mat4 translation_matrix = Mat4::translation_matrix(position);
        Mat4 rotation_matrix = Mat4::rotation_matrix(orientation);
        return scalar_matrix * translation_matrix * rotation_matrix;
    }
}

