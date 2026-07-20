
/****************/
/*   mesh.cpp   */
/****************/

#include "rendering.h"

namespace Vi {
	
	/* Public */

	Vec3<double> Mesh::forward() const {
		const Vec3<double> forward_basis = Vec3<double>::zneg();
		return Rotation::applyRotation(forward_basis, orientation.quat);
	}

	Vec3<double> Mesh::up() const {
		const Vec3<double> up_basis = Vec3<double>::ypos();
		return Rotation::applyRotation(up_basis, orientation.quat);
	}

	Vec3<double> Mesh::right() const {
		const Vec3<double> right_basis = Vec3<double>::xpos();
		return Rotation::applyRotation(right_basis, orientation.quat);
	}

	void Mesh::rotate(const Vec3<double>& axis, double theta) {
		Quaternion rotation = Rotation::makeRotation(axis, theta);
		orientation.quat = rotation * orientation.quat;
	}

	/* Private */

	Matrix<double> Mesh::modelMatrix() const {
		Matrix<double> scalar_matrix = Matrix<double>::scalar(scale);
		Matrix<double> translation_matrix = Matrix<double>::translation(position);
		Matrix<double> rotation_matrix = Matrix<double>::rotation(orientation.quat);
		return scalar_matrix * translation_matrix * rotation_matrix;
	}
}

