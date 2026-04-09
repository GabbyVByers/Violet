
/*
    Mesh.cpp
*/

#include "Violet.h"

namespace Vi {

    void Mesh::paint(const Color& color) {
        for (Vertex& vertex : vertices) {
            vertex.color = color;
        }
    }
}

