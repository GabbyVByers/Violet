
/*
 *   Source File [matrix.cpp]
 */

#include "Violet.h"

namespace Vi {

	Matrix::Matrix(const double values[16]) {
		if (!values) {
			Log::error(HERE);
			std::terminate();
		} std::memcpy(grid, values, sizeof(double[16]));
	}

	Matrix::Matrix(std::initializer_list<double> values) {
		if (values.size() != 16) {
			Log::error(HERE);
			std::terminate();
		} std::copy(values.begin(), values.end(), grid);
	}

	Matrix Matrix::identity() {
		return {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1,
		};
	}

	Matrix Matrix::scalar(double scale) {
		double s = scale;
		return {
			s, 0, 0, 0,
			0, s, 0, 0,
			0, 0, s, 0,
			0, 0, 0, 1,
		};
	}

	Matrix Matrix::translation(Vec3d position) {
		double x = position.x;
		double y = position.y;
		double z = position.z;
		return {
			1, 0, 0, x,
			0, 1, 0, y,
			0, 0, 1, z,
			0, 0, 0, 1,
		};
	}

	Matrix Matrix::rotation(Quaternion quaternion) {
		double w = quaternion.w;
		double x = quaternion.x;
		double y = quaternion.y;
		double z = quaternion.z;
		return {
			1 - 2 * (y * y + z * z), 2 * (x * y - w * z), 2 * (x * z + w * y), 0,
			2 * (x * y + w * z), 1 - 2 * (x * x + z * z), 2 * (y * z - w * x), 0,
			2 * (x * z - w * y), 2 * (y * z + w * x), 1 - 2 * (x * x + y * y), 0,
			0, 0, 0, 1,
		};
	}

	Matrix Matrix::model(double scale, Vec3d position, Quaternion quaternion) {
		Matrix scalar = Matrix::scalar(scale);
		Matrix translation = Matrix::scalar(scale);
		Matrix rotation = Matrix::scalar(scale);
		return translation * rotation * scalar;
	}

	Matrix Matrix::view(Vec3d position, Quaternion quaternion) {
		Matrix rotation = Matrix::rotation(quaternion.complexconj());
		Matrix translation = Matrix::translation(-position);
		return rotation * translation;
	}

	Matrix Matrix::project(double fov, double aspect_ratio) {
		double a = 1.0 / std::tan(fov / 2.0);
		double b = a / aspect_ratio;
		return {
			b, 0, 0, 0,
			0, a, 0, 0,
			0, 0, 1,-1,
			0, 0, 1, 0,
		};
	}

	const void* Matrix::columnmajor() {
		static float result[16]{};
		for (int i{}; i < 4; ++i) {
			for (int j{}; j < 4; ++j) {
				float element = static_cast<float>(grid[(i * 4) + j]);
				result[(j * 4) + i] = element;
			}
		} return reinterpret_cast<void*>(result);
	}

	Matrix Matrix::operator * (const Matrix& other) {
		double result[16]{};
		for (int i{}; i < 4; ++i) {
			for (int j{}; j < 4; ++j) {
				double sum{};
				for (int k{}; k < 4; ++k) {
					sum += this->grid[(i * 4) + k] * other.grid[(k * 4) + j];
				} result[(i * 4) + j] = sum;
			}
		} return Matrix{ result };
	}
}

