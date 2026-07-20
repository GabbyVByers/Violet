
/******************/
/*   sprite.cpp   */
/******************/

#include "rendering.h"

namespace Vi {
	
	Sprite::Sprite(const Texture& tex) {
		texture = tex;
		size.x = tex.image.width();
		size.y = tex.image.height();
		Vertex tl{ {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f}, {} };
		Vertex tr{ {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, {} };
		Vertex bl{ {0.0f,-1.0f, 0.0f}, {0.0f, 0.0f}, {} };
		Vertex br{ {1.0f,-1.0f, 0.0f}, {1.0f, 0.0f}, {} };
		std::vector<Vertex> verts = { tl, tr, bl, tr, br, bl };
		vertices.insert(vertices.begin(), verts.begin(), verts.end());
	}

	Matrix<double> Sprite::modelMatrix() const {
		GLFWwindow* window = glfwGetCurrentContext();
		assert(window != nullptr);
		int ix, iy; glfwGetFramebufferSize(window, &ix, &iy);
		double dx = double(ix), dy = double(iy);
		double aspect_ratio = dx / dy;
		double x = 2.0 * (double(size.x) / dx);
		double y = 2.0 * (double(size.y) / dy);
		Matrix<double> scalar_matrix = Matrix<double>(
			x, 0, 0, 0,
			0, y, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
		double px = ((double(position.x) / dx) * 2.0) - 1.0;
		double py = (1.0 - ((double(position.y) / dy) * 2.0));
		Matrix<double> translation_matrix = Matrix<double>::translation(Vec3<double>{px, py, 0.0});
		return translation_matrix * scalar_matrix;
	}
}

