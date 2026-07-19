
/* vec3.h */

#pragma once

#include <cmath>
#include <concepts>
#include <cassert>

#ifndef Vi
#define Vi Vi
#endif /* Vi */

namespace Vi {

	template<std::integral type>
	class Vec3i {
	public:
		type x{};
		type y{};
		type z{};
	};

	template<std::floating_point type>
	class Vec3 {
	public:
		type x{}, y{}, z{};
		Vec3 operator + (const Vec3& v) const { return Vec3{ x + v.x, y + v.y, z + v.z }; }
		Vec3 operator - (const Vec3& v) const { return Vec3{ x - v.x, y - v.y, z - v.z }; }
		Vec3 operator * (const type s) const { return Vec3{ x * s, y * s, z * s }; }
		Vec3 operator / (const type s) const { return Vec3{ x / s, y / s, z / s }; }
		Vec3& operator += (const Vec3& v) { x += v.x; y += v.y; z += v.z; return *this; }
		Vec3& operator -= (const Vec3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
		Vec3& operator *= (const type s) { x *= s; y *= s; z *= s; return *this; }
		Vec3& operator /= (const type s) { x /= s; y /= s; z /= s; return *this; }
		Vec3 operator - () const { return Vec3{ -x, -y, -z }; }
		friend Vec3 operator * (type s, const Vec3& v) { return v * s; }
		type length() const;
		Vec3& normalize();
		Vec3& rotate(const Vec3&, const type);
		static type dot(const Vec3&, const Vec3&);
		static Vec3 cross(const Vec3&, const Vec3&);
		static type angle(const Vec3&, const Vec3&);
		static Vec3 xpos() { return Vec3{ (type) 1, (type) 0, (type) 0 }; }
		static Vec3 xneg() { return Vec3{ (type)-1, (type) 0, (type) 0 }; }
		static Vec3 ypos() { return Vec3{ (type) 0, (type) 1, (type) 0 }; }
		static Vec3 yneg() { return Vec3{ (type) 0, (type)-1, (type) 0 }; }
		static Vec3 zpos() { return Vec3{ (type) 0, (type) 0, (type) 1 }; }
		static Vec3 zneg() { return Vec3{ (type) 0, (type) 0, (type)-1 }; }
		template<typename cast>
		operator Vec3<cast>() const { return Vec3<cast>{ (cast)x, (cast)y, (cast)z }; }
	};

	template<std::floating_point type>
	type Vec3<type>::length() const {
		return std::hypot(x, y, z);
	}

	template<std::floating_point type>
	Vec3<type>& Vec3<type>::normalize() {
		type length = std::hypot(x, y, z);
		x /= length; y /= length; z /= length;
		return *this;
	}

	template<std::floating_point type>
	Vec3<type>& Vec3<type>::rotate(const Vec3& axis, const type theta) {
		const type len = axis.length();
		const Vec3<type> k = Vec3<type>{ axis.x / len, axis.y / len, axis.z / len };
		const Vec3<type> v = Vec3<type>{ x, y, z };
		const Vec3<type> kv_cross = Vec3<type>::cross(k, v);
		const type kv_dot = Vec3<type>::dot(k, v);
		const type c = std::cos(theta);
		const type s = std::sin(theta);
		const Vec3<type> result = (v * c) + (kv_cross * s) + (k * (kv_dot * (1.0 - c)));
		x = result.x; y = result.y; z = result.z;
		return *this;
	}

	template<std::floating_point type>
	type Vec3<type>::dot(const Vec3& a, const Vec3& b) {
		type xx = a.x * b.x;
		type yy = a.y * b.y;
		type zz = a.z * b.z;
		return xx + yy + zz;
	}

	template<std::floating_point type>
	Vec3<type> Vec3<type>::cross(const Vec3& a, const Vec3& b) {
		return Vec3{
			(a.y * b.z) - (a.z * b.y),
			(a.z * b.x) - (a.x * b.z),
			(a.x * b.y) - (a.y * b.x)
		};
	}

	template<std::floating_point type>
	type Vec3<type>::angle(const Vec3& a, const Vec3& b) {
		type product = a.length() * b.length();
		return std::acos(dot(a, b) / product);
	}
}

