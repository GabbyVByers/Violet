
/****************/
/*   mesh.cpp   */
/****************/

#include "rendering.h"

namespace Vi {
	
	/* Public */

	Vec3<double> Mesh::forward() const {
		const Vec3<double> forward_basis = Vec3<double>::zneg();
		return Quaternion::apply(forward_basis, orientation);
	}

	Vec3<double> Mesh::up() const {
		const Vec3<double> up_basis = Vec3<double>::ypos();
		return Quaternion::apply(up_basis, orientation);
	}

	Vec3<double> Mesh::right() const {
		const Vec3<double> right_basis = Vec3<double>::xpos();
		return Quaternion::apply(right_basis, orientation);
	}

	void Mesh::rotate(const Vec3<double>& axis, double theta) {
		Quaternion rotation = Quaternion::create(axis, theta);
		orientation = rotation * orientation;
	}

	void Mesh::update() {
		upload = true;
	}

	/* Private */

	Matrix<double> Mesh::modelMatrix() const {
		Matrix<double> scalar_matrix = Matrix<double>::scalar(scale);
		Matrix<double> translation_matrix = Matrix<double>::translation(position);
		Matrix<double> rotation_matrix = Matrix<double>::rotation(orientation);
		return scalar_matrix * translation_matrix * rotation_matrix;
	}
}

