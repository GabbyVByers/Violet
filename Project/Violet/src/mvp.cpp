
/***************/
/*   mvp.cpp   */
/***************/

#include "rendering.h"
#include <numbers>
#include <cmath>

namespace Vi {
	
	/* MODEL */

	Matrix<double> Mesh::modelMatrix() const {
		Matrix<double> scalar_matrix = Matrix<double>::scalar(scale);
		Matrix<double> translation_matrix = Matrix<double>::translation(position);
		Matrix<double> rotation_matrix = Matrix<double>::rotation(orientation.quat);
		return scalar_matrix * translation_matrix * rotation_matrix;
	}

	/* VIEW */
	
	Matrix<double> Camera::viewMatrix() {
		Matrix<double> translation_matrix_inverse = Matrix<double>::translation(-position);
		Matrix<double> rotation_matrix_inverse = Matrix<double>::rotation(orientation.quat.complexconj());
		return rotation_matrix_inverse * translation_matrix_inverse;
	}
	
	/* PROJECT */

	Matrix<double> Camera::projectionMatrix() {
		GLFWwindow* window = glfwGetCurrentContext();
		assert(window != nullptr);
		int ix, iy; glfwGetFramebufferSize(window, &ix, &iy);
		double dx = double(ix), dy = double(iy);
		double fov_rad = (fov / 180.0) * std::numbers::pi;
		double f = 1.0 / std::tan(fov_rad * 0.5);
		double a = dx / dy;
		double A = f / a;
		double D = -2.0 * near;
		return Matrix<double>(
			A, 0, 0, 0,
			0, f, 0, 0,
			0, 0,-1, D,
			0, 0,-1, 0
		);
	}
}

