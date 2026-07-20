
/********************/
/*   rotation.cpp   */
/********************/

#include "algebra.h"

namespace Vi {
	
	/* Public */

	Vec3<double> Rotation::forward() const {
		const Vec3<double> forward_basis = Vec3<double>::zneg();
		return applyRotation(forward_basis, quat);
	}

	Vec3<double> Rotation::up() const {
		const Vec3<double> up_basis = Vec3<double>::ypos();
		return applyRotation(up_basis, quat);
	}

	Vec3<double> Rotation::right() const {
		const Vec3<double> right_basis = Vec3<double>::xpos();
		return applyRotation(right_basis, quat);
	}

	void Rotation::rotate(const Vec3<double>& axis, double theta) {
		Quaternion rotation = makeRotation(axis, theta);
		quat = rotation * quat;
	}

	Quaternion Rotation::makeRotation(const Vec3<double>& axis, double theta) {
		double half = theta / double(2);
		double sine = std::sin(half);
		return Quaternion{
			std::cos(half),
			sine * axis.x,
			sine * axis.y,
			sine * axis.z
		};
	}

	Vec3<double> Rotation::applyRotation(const Vec3<double>& vec, const Quaternion& rotation) {
		Quaternion complex = rotation.complexconj();
		Quaternion pure = Quaternion{ 0.0, vec.x, vec.y, vec.z };
		Quaternion result = rotation * pure * complex;
		return Vec3<double>{
			result.x,
			result.y,
			result.z
		};
	}
}

