
/*
 *   Header File [Violet.h]
 */

#pragma once

#include "SDL3/SDL.h"
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlgpu3.h"

#include <iostream>
#include <fstream>
#include <format>
#include <filesystem>
#include <limits>

namespace Vi {

	class Window;

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
		static Vec2 xpos() { return { 1, 0 }; }
		static Vec2 xneg() { return {-1, 0 }; }
		static Vec2 ypos() { return { 0, 1 }; }
		static Vec2 yneg() { return { 0,-1 }; }
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
		static Vec3 xpos() { return { 1, 0, 0 }; }
		static Vec3 xneg() { return {-1, 0, 0 }; }
		static Vec3 ypos() { return { 0, 1, 0 }; }
		static Vec3 yneg() { return { 0,-1, 0 }; }
		static Vec3 zpos() { return { 0, 0, 1 }; }
		static Vec3 zneg() { return { 0, 0,-1 }; }
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
		Quaternion complexconj() const { return { w, -x, -y, -z }; }
		Quaternion operator * (const Quaternion& other) {
			const Quaternion& a = *this;
			const Quaternion& b = other;
			return {
				.w = (a.w * b.w) - (a.x * b.x) - (a.y * b.y) - (a.z * b.z),
				.x = (a.w * b.x) + (a.x * b.w) + (a.y * b.z) - (a.z * b.y),
				.y = (a.w * b.y) - (a.x * b.z) + (a.y * b.w) + (a.z * b.x),
				.z = (a.w * b.z) + (a.x * b.y) - (a.y * b.x) + (a.z * b.w),
			};
		}
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

		static Vec3d forward() {
			Vec3d direction = Vec3d::zpos();
			return {};
		}

		static Vec3d right() {
			Vec3d direction = Vec3d::xpos();
			return {};
		}

		static Vec3d up() {
			Vec3d direction = Vec3d::ypos();
			return {};
		}
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
	public:
		static void hide();
		static void reveal();
		static bool pressing(int);
		static bool pressed(int);
		static bool released(int);
		static Vec2f position();
		static Vec2f velocity();

	private:
		friend Window;
		static inline Vec2f saved_position{};
		static inline Vec2f pos{};
		static inline Vec2f vel{};
		static inline int prev_state{};
		static inline int curr_state{};

		Mouse() = delete;
		Mouse(const Mouse&) = delete;
		Mouse(Mouse&&) = delete;
	};

	class Keyboard {
	public:
		static bool pressing(int);
		static bool pressed(int);
		static bool released(int);

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
		Window(const char*, int, int, bool = false);
		~Window();
		void vsync(bool);
		bool isOpen();
		void clear(Color);
		void draw(const Mesh&);
		void display();

	private:
		friend Mesh;
		friend Mouse;
		friend Keyboard;
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

