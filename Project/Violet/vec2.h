
/* vec2.h */

#pragma once

#include <cmath>
#include <concepts>
#include <cassert>

#ifndef Vi
#define Vi Vi
#endif /* Vi */

namespace Vi {
	
	template<std::integral type>
	class Vec2i {
	public:
		type x{};
		type y{};
	};

	template<std::floating_point type>
	class Vec2 {
	public:
		type x{}, y{};
		Vec2 operator + (const Vec2& v) const { return Vec2{ x + v.x, y + v.y }; }
		Vec2 operator - (const Vec2& v) const { return Vec2{ x - v.x, y - v.y }; }
		Vec2 operator * (const type s) const { return Vec2{ x * s, y * s }; }
		Vec2 operator / (const type s) const { return Vec2{ x / s, y / s }; }
		Vec2& operator += (const Vec2& v) { x += v.x; y += v.y; return *this; }
		Vec2& operator -= (const Vec2& v) { x -= v.x; y -= v.y; return *this; }
		Vec2& operator *= (const type s) { x *= s; y *= s; return *this; }
		Vec2& operator /= (const type s) { x /= s; y /= s; return *this; }
		Vec2 operator - () const { return Vec2{ -x, -y }; }
		friend Vec2 operator * (type s, const Vec2& v) { return v * s; }
		type length() const;
		Vec2& normalize();
		Vec2& rotate(type);
		static type dot(const Vec2&, const Vec2&);
		static type cross(const Vec2&, const Vec2&);
		static type angle(const Vec2&, const Vec2&);
		static Vec2 xpos() { return Vec2{(type) 1, (type) 0}; }
		static Vec2 xneg() { return Vec2{(type)-1, (type) 0}; }
		static Vec2 ypos() { return Vec2{(type) 0, (type) 1}; }
		static Vec2 yneg() { return Vec2{(type) 0, (type)-1}; }
		template<std::floating_point cast>
		operator Vec2<cast>() const { return Vec2<cast>{(cast)x, (cast)y}; }
	};

	template<std::floating_point type>
	type Vec2<type>::length() const {
		return std::hypot((type)x, (type)y);
	}

	template<std::floating_point type>
	Vec2<type>& Vec2<type>::normalize() {
		type length = std::hypot((type)x, (type)y);
		x /= length; y /= length;
		return *this;
	}

	template<std::floating_point type>
	Vec2<type>& Vec2<type>::rotate(type theta) {
		type xnew = x * std::cos(theta) - y * std::sin(theta);
		type ynew = x * std::sin(theta) + y * std::cos(theta);
		x = xnew; y = ynew;
		return *this;
	}

	template<std::floating_point type>
	type Vec2<type>::dot(const Vec2& a, const Vec2& b) {
		type xx = a.x * b.x;
		type yy = a.y * b.y;
		return xx + yy;
	}
	
	template<std::floating_point type>
	type Vec2<type>::cross(const Vec2& a, const Vec2& b) {
		type axby = a.x * b.y;
		type aybx = a.y * b.x;
		return axby - aybx;
	}

	template<std::floating_point type>
	type Vec2<type>::angle(const Vec2& a, const Vec2& b) {
		return std::atan2(cross(a, b), dot(a, b));
	}
}

