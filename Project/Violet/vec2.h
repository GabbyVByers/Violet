
/* vec2.h */

#pragma once

#include <cmath>
#include <numbers>

#ifndef Vi
#define Vi Vi
#endif /* Vi */

namespace Vi {
	
	template<typename type>
	class Vec2 {
	public:
		type x{}, y{};
		Vec2 operator + (const Vec2 v) const { return Vec2{ x + v.x, y + v.y }; }
		Vec2 operator - (const Vec2 v) const { return Vec2{ x - v.x, y - v.y }; }
		Vec2 operator * (const type s) const { return Vec2{ x * s, y * s }; }
		Vec2 operator / (const type s) const { return Vec2{ x / s, y / s }; }
		Vec2& operator += (const Vec2 v) { x += v.x; y += v.y; }
		Vec2& operator -= (const Vec2 v) { x -= v.x; y -= v.y; }
		Vec2& operator *= (const type s) { x *= s; y *= s; }
		Vec2& operator /= (const type s) { x /= s; y /= s; }
		double length() const;
		Vec2& normalize();
		Vec2& rotate(double);
		static double dot(const Vec2&, const Vec2&);
		static double cross(const Vec2&, const Vec2&);
		static double angle(const Vec2&, const Vec2&);
		static Vec2 xpos() { return Vec2{ (type) 1, (type) 0 }; }
		static Vec2 xneg() { return Vec2{ (type)-1, (type) 0 }; }
		static Vec2 ypos() { return Vec2{ (type) 0, (type) 1 }; }
		static Vec2 yneg() { return Vec2{ (type) 0, (type)-1 }; }
		template <typename cast>
		operator Vec2<cast>() { return Vec2<cast>{(cast)x, (cast)y}; }
	};

	template<typename type>
	double Vec2<type>::length() const {
		return std::hypot((double)x, (double)y);
	}

	template<typename type>
	Vec2<type>& Vec2<type>::normalize() {
		double length = std::hypot((double)x, (double)y);
		x /= length; y /= length;
		return *this;
	}

	template<typename type>
	Vec2<type>& Vec2<type>::rotate(double theta) {
		double xnew = x * std::cos(theta) - y * std::sin(theta);
		double ynew = y * std::sin(theta) + y * std::cos(theta);
		x = xnew; y = ynew;
		return *this;
	}

	template<typename type>
	double Vec2<type>::dot(const Vec2& a, const Vec2& b) {
		double xx = a.x * b.x;
		double yy = a.y * b.y;
		return xx + yy;
	}
	
	template<typename type>
	double Vec2<type>::cross(const Vec2& a, const Vec2& b) {
		double axby = a.x * b.y;
		double aybx = a.y * b.x;
		return axby - aybx;
	}

	template<typename type>
	double Vec2<type>::angle(const Vec2& a, const Vec2& b) {
		double atan2_a = std::atan2(a.y, a.x);
		double atan2_b = std::atan2(b.y, b.x);
		double difference = std::abs(atan2_a - atan2_b);
		return (difference > std::numbers::pi) ?
			((2.0 * std::numbers::pi) - difference) :
			(difference);
	}
}

