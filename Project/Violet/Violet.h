
/*
 *   Header File [Violet.h]
 */

#pragma once

#include "SDL3/SDL.h"
#include <iostream>
#include <fstream>
#include <format>
#include <filesystem>
#include <limits>

namespace Vi {

	template<typename type>
	class Vec2 {
	public:
		type x{}, y{};
		Vec2 operator + (const Vec2& vec)  const { return { x + vec.x, y + vec.y }; }
		Vec2 operator - (const Vec2& vec)  const { return { x - vec.x, y - vec.y }; }
		Vec2 operator * (type scale) const { return { x * scale, y * scale }; }
		Vec2 operator / (type scale) const { return { x / scale, y / scale }; }
		Vec2& operator += (const Vec2& vec)  { x += vec.x; y += vec.y; return *this; }
		Vec2& operator -= (const Vec2& vec)  { x -= vec.x; y -= vec.y; return *this; }
		Vec2& operator *= (type scale) { x *= scale; y *= scale; return *this; }
		Vec2& operator /= (type scale) { x /= scale; y /= scale; return *this; }
		Vec2 operator - () const { return { -x, -y }; }
		friend Vec2 operator * (type scale, const Vec2& vec) { return vec * scale; }
	};

	template<typename type>
	class Vec3 {
	public:
		type x{}, y{}, z{};
		Vec3 operator + (const Vec3& vec)  const { return { x + vec.x, y + vec.y, z + vec.z }; }
		Vec3 operator - (const Vec3& vec)  const { return { x - vec.x, y - vec.y, z - vec.z }; }
		Vec3 operator * (type scale) const { return { x * scale, y * scale, z * scale }; }
		Vec3 operator / (type scale) const { return { x / scale, y / scale, z / scale }; }
		Vec3& operator += (const Vec3& vec)  { x += vec.x; y += vec.y; z += vec.z; return *this; }
		Vec3& operator -= (const Vec3& vec)  { x -= vec.x; y -= vec.y; z -= vec.z; return *this; }
		Vec3& operator *= (type scale) { x *= scale; y *= scale; z *= scale; return *this; }
		Vec3& operator /= (type scale) { x /= scale; y /= scale; z /= scale; return *this; }
		Vec3 operator - () const { return { -x, -y, -z }; }
		friend Vec3 operator * (type scale, const Vec3& vec) { return vec * scale; }
	};

	typedef Vec2<float>  Vec2f;
	typedef Vec2<double> Vec2d;
	typedef Vec2<int>    Vec2i;
	typedef Vec2<size_t> Vec2u;

	typedef Vec3<float>  Vec3f;
	typedef Vec3<double> Vec3d;
	typedef Vec3<int>    Vec3i;
	typedef Vec3<size_t> Vec3u;

	struct Color {
		float r{}, g{}, b{}, a{ 1.0 };
	};

	struct Vertex {
		Vec3f pos{};
		Color color{};
		Vec2f uv{};
	};

	class Quaternion {
	public:
		double w{ 1.0 }, x{}, y{}, z{};
		Quaternion complexconj() { return { w, -x, -y, -z }; }
	};

	class Matrix {
	public:
		Matrix() = delete;
		Matrix(const double[16]);
		Matrix(std::initializer_list<double>);

		static Matrix identity();
		static Matrix scalar(double);
		static Matrix translation(Vec3d);
		static Matrix rotation(Quaternion);

		static Matrix model(double, Vec3d, Quaternion);
		static Matrix view(Vec3d, Quaternion);
		static Matrix project(double, double);
		Matrix operator * (const Matrix&);

	private:
		double grid[16];
	};

	class Image {
	public:
		Image() = default;
		Image(Vec2u);
		Image(std::filesystem::path);
		static Image perlin(Vec2u, size_t, double);
		~Image();
		
		Image(const Image&);
		Image(Image&&) noexcept;
		Image& operator = (const Image&);
		Image& operator = (Image&&) noexcept;

		void putPixel(Vec2u, Color);
		Color getPixel(Vec2u) const;
		const uint8_t* ptr(size_t&) const;
		Vec2u size() const;
	
	private:
		uint8_t* pixels{};
		Vec2u dimensions{};
	};

	class Camera {
	public:



	};

	class Mesh {
	public:



	};

	class Window {
	public:
		Window(const char*, int, int);
		~Window();
		bool isOpen();
		void clear(Color);
		void draw(const Mesh&);
		void display();

	private:
		friend Mesh;
		Window(const Window&) = delete;
		Window(Window&&) = delete;
		void operator = (const Window&) = delete;
		void operator = (Window&&) = delete;

		static inline bool created{};
		static inline int screen_width{};
		static inline int screen_height{};
		static inline SDL_Window* window{};
		static inline SDL_GPUDevice* device{};
		static inline SDL_GPUTexture* depth_texture{};
		static inline SDL_GPUSampler* sampler{};
		static inline SDL_GPUGraphicsPipeline* graphics_pipeline{};

		static inline bool frame{};
		static inline bool minimized{};
		static inline SDL_GPURenderPass* render_pass{};
		static inline SDL_GPUTexture* swapchain_texture{};
		static inline SDL_GPUCommandBuffer* command_buffer{};
	};
}

