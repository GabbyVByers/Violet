
/******************/
/*   camera.cpp   */
/******************/

#include "rendering.h"
#include <numbers>
#include <cmath>

namespace Vi {
	
	/* Public */

	Vec3<double> Camera::forward() {
		const Vec3<double> forward_basis = Vec3<double>::zneg();
		return Quaternion::apply(forward_basis, orientation);
	}

	Vec3<double> Camera::up() {
		const Vec3<double> up_basis = Vec3<double>::ypos();
		return Quaternion::apply(up_basis, orientation);
	}

	Vec3<double> Camera::right() {
		const Vec3<double> right_basis = Vec3<double>::xpos();
		return Quaternion::apply(right_basis, orientation);
	}

	void Camera::rotate(const Vec3<double>& axis, double theta) {
		Quaternion rotation = Quaternion::create(axis, theta);
		orientation = rotation * orientation;
	}

	/* Private */

	Matrix<double> Camera::viewMatrix() {
		Matrix<double> translation_matrix_inverse = Matrix<double>::translation(-position);
		Matrix<double> rotation_matrix_inverse = Matrix<double>::rotation(orientation.complexconj());
		return rotation_matrix_inverse * translation_matrix_inverse;
	}

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

