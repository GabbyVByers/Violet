
/**********************/
/*   quaternion.cpp   */
/**********************/

#include "algebra.h"

namespace Vi {

	/* Public */

	void Quaternion::normalize() {
		double len = std::hypot(x, y, z);
		len = std::hypot(len, w);
		w /= len; x /= len;
		y /= len; z /= len;
	}

	Quaternion Quaternion::complexconj() const {
		return Quaternion{ w, -x, -y, -z };
	}

	Quaternion Quaternion::operator * (const Quaternion& other) const {
		const Quaternion& a = *this;
		const Quaternion& b = other;
		return Quaternion{
			(a.w * b.w) - (a.x * b.x) - (a.y * b.y) - (a.z * b.z),
			(a.w * b.x) + (a.x * b.w) + (a.y * b.z) - (a.z * b.y),
			(a.w * b.y) - (a.x * b.z) + (a.y * b.w) + (a.z * b.x),
			(a.w * b.z) + (a.x * b.y) - (a.y * b.x) + (a.z * b.w)
		};
	}
}

