
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

#ifdef HERE
#undef HERE
#endif /* HERE */
#define HERE __FILE__, __LINE__

namespace Vi {

	class Window;

	namespace Log {
		void error(const char*, int);
		void error(const char*);
		void error(const std::string&);
	}

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

		const void* columnmajor();
		Matrix operator * (const Matrix&);

	private:
		double grid[16];
	};

	class Image {
	public:
		
		Image(Vec2u = {1,1});
		Image(std::filesystem::path);
		Image(Vec2u, size_t, double);
		~Image();

		Image(const Image&);
		Image(Image&&) noexcept;
		Image& operator = (const Image&);
		Image& operator = (Image&&) noexcept;

		void putPixel(Vec2u, Color);
		Color getPixel(Vec2u) const;
		const uint8_t* ptr() const;
		Vec2u size() const;
	
	private:
		uint8_t* pixels{};
		Vec2u dimensions{};
	};

	class Camera {
	public:

		static inline double fov{ 2.0 };
		static inline Vec3d position{};
		static inline Quaternion quaternion{};
	};

	class Mesh {
	public:
		Mesh(const Image& = {});
		~Mesh();
		void upload(const Vertex*, size_t);

		double scale{ 1.0 };
		Vec3d position{};

	private:
		friend Window;
		Mesh(const Mesh&) = delete;
		Mesh(Mesh&&) = delete;
		void operator = (const Mesh&) = delete;
		void operator = (Mesh&&) = delete;

		size_t num_vertices{};
		SDL_GPUBuffer* vertex_buffer{};
		SDL_GPUTexture* gpu_texture{};
		Quaternion quaternion{};
		void texture(const Image&);
	};

	class Mouse {

	};

	class Keyboard {
	public:
		static bool pressed(int);
		static bool released(int);
		static bool pressing(int);

	private:
		friend Window;
		static inline bool curr_keys[SDL_SCANCODE_COUNT]{};
		static inline bool prev_keys[SDL_SCANCODE_COUNT]{};

		Keyboard() = delete;
		Keyboard(const Keyboard&) = delete;
		Keyboard(Keyboard&&) = delete;
	};

	class Window {
	public:
		Window(const char*, int, int);
		~Window();
		void vsync(bool);
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
		static inline Vec2u dimensions{};
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

