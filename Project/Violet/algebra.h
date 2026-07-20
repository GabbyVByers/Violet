
/*****************/
/*   algebra.h   */
/*****************/

#pragma once

#include "vec2.h"
#include "vec3.h"
#include <concepts>
#include <cmath>

#ifndef Vi
#define Vi Vi
#endif /* Vi */

namespace Vi {
	
	/************************************/
	/*   Quaternion, Rotation, Matrix   */
	/************************************/

	class Quaternion {
	public:
		double w{1.0};
		double x{0.0};
		double y{0.0};
		double z{0.0};
		void normalize();
		Quaternion complexconj() const;
		Quaternion operator * (const Quaternion&) const;
	};

	class Rotation {
	public:
		Vec3<double> forward() const;
		Vec3<double> up() const;
		Vec3<double> right() const;
		void rotate(const Vec3<double>&, double);
		static Quaternion makeRotation(const Vec3<double>&, double);
		static Vec3<double> applyRotation(const Vec3<double>&, const Quaternion&);
		Quaternion quat{};
	};

	template<std::floating_point type>
	class Matrix {
	public:
		Matrix() {
			for (size_t i{}; i < 4; i++) {
				for (size_t j{}; j < 4; j++) {
					data[i][j] = type(0);
				} data[i][i] = type(1);
			}
		}

		Matrix(
			type a, type b, type c, type d,
			type e, type f, type g, type h,
			type i, type j, type k, type l,
			type m, type n, type o, type p
		) {
			data[0][0] = a; data[0][1] = b; data[0][2] = c; data[0][3] = d;
			data[1][0] = e; data[1][1] = f; data[1][2] = g; data[1][3] = h;
			data[2][0] = i; data[2][1] = j; data[2][2] = k; data[2][3] = l;
			data[3][0] = m; data[3][1] = n; data[3][2] = o; data[3][3] = p;
		}

		static Matrix scalar(const type s) {
			return Matrix(
				s, 0, 0, 0,
				0, s, 0, 0,
				0, 0, s, 0,
				0, 0, 0, 1
			);
		}

		static Matrix translation(const Vec3<type>& p) {
			return Matrix(
				1, 0, 0, p.x,
				0, 1, 0, p.y,
				0, 0, 1, p.z,
				0, 0, 0, 1
			);
		}

		static Matrix rotation(const Quaternion& q) {
			const type w = q.w, x = q.x, y = q.y, z = q.z;
			return Matrix(
				1 - 2 * (y * y + z * z), 2 * (x * y - z * w), 2 * (x * z + y * w), 0,
				2 * (x * y + z * w), 1 - 2 * (x * x + z * z), 2 * (y * z - x * w), 0,
				2 * (x * z - y * w), 2 * (y * z + x * w), 1 - 2 * (x * x + y * y), 0,
				0, 0, 0, 1
			);
		}

		type* get() const {
			return (type*)data;
		}

		Matrix operator * (const Matrix& other) const {
			Matrix result{};
			for (size_t i{}; i < 4; i++) {
				for (size_t j{}; j < 4; j++) {
					type sum = 0;
					for (size_t k{}; k < 4; k++) {
						sum += data[i][k] * other.data[k][j];
					} result.data[i][j] = sum;
				}
			} return result;
		}
		
		template<std::floating_point cast>
		explicit operator Matrix<cast>() const {
			return Matrix<cast>(
				cast(data[0][0]), cast(data[0][1]), cast(data[0][2]), cast(data[0][3]),
				cast(data[1][0]), cast(data[1][1]), cast(data[1][2]), cast(data[1][3]),
				cast(data[2][0]), cast(data[2][1]), cast(data[2][2]), cast(data[2][3]),
				cast(data[3][0]), cast(data[3][1]), cast(data[3][2]), cast(data[3][3])
			);
		}

	private:
		type data[4][4]{};
	};
}

