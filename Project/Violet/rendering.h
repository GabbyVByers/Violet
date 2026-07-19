
/*******************/
/*   rendering.h   */
/*******************/

#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "algebra.h"
#include "vec2.h"
#include "vec3.h"

#ifndef Vi
#define Vi Vi
#endif /* Vi */

namespace Vi {

	/***************************************************/
	/*        Color, Vertex, Mesh, Sprite, Text        */
	/***************************************************/

	class Color;
	class Vertex;

	class Color {
	public:
		static Color white();
		static Color black();
		static Color red();
		static Color green();
		static Color blue();
		float r{1.0f};
		float g{1.0f};
		float b{1.0f};
		float a{1.0f};
	};

	class Vertex {
	public:
		Vec3<float> position{};
		Vec2<float> texCoord{};
		Color color{};
	};

	/***************************************************/
	/*             Image, Texture, Material            */
	/***************************************************/

	class Image;
	class Texture;
	class Material;

	class Image {
	public:
		Image(const Vec2i<size_t>& = Vec2i<size_t>{1, 1});
		Image(const char*);
		Image(const Image&)                  = default;
		Image(Image&&) noexcept              = default;
		Image& operator = (const Image&)     = default;
		Image& operator = (Image&&) noexcept = default;
		~Image()                             = default;
		size_t width() const;
		size_t height() const;
		Color getPixel(const Vec2i<size_t>&) const;
		void setPixel(const Vec2i<size_t>&, const Color&);
	private:
		friend Texture;
		Vec2i<size_t> size{};
		std::shared_ptr<unsigned char[]> pixels{};
	};

	class Texture {
	public:
		Texture(const Image& = Image{});
		Texture(const Texture&);
		Texture(Texture&&) noexcept;
		Texture& operator = (const Texture&);
		Texture& operator = (Texture&&) noexcept;
		~Texture();
	private:
		void generate();
		void destroy();
		Image image{};
		GLuint glTextureID{};
	};

	class Material {
	public:
		Material();
		Material(const Material&);
		Material(Material&& other) noexcept;
		Material& operator = (const Material&);
		Material& operator = (Material&& other) noexcept;
		~Material();
	private:
		void generate();
		void destroy();
		GLuint VAO{};
		GLuint VBO{};
	};

	/***************************************************/
	/*                Mesh, Sprite, Text               */
	/***************************************************/

	class Mesh;
	class Sprite;
	class Text;

	class Mesh {
	public:
		std::vector<Vertex> vertices{};
		double scale{};
		Vec3<double> position{};
		Quaternion orientation{};
	private:
		Texture texture{};
		Material material{};
	};

	class Sprite {
	public:
	private:
	};

	class Text {
	public:
	private:
	};

	/***************************************************/
	/*             Keyboard, Mouse, Window             */
	/***************************************************/

	class Keyboard;
	class Mouse;
	class Window;

	class Keyboard {
	public:
		static bool pressed(int, int);
		static bool pressing(int);
	private:
		friend Window;
		struct KeyboardEvent { int key, scancode, action, mods; };
		static inline std::vector<KeyboardEvent> keyboard_events{};
		Keyboard()                        = delete;
		Keyboard(const Keyboard&)         = delete;
		Keyboard(Keyboard&&)              = delete;
		void operator = (const Keyboard&) = delete;
		void operator = (Keyboard&&)      = delete;
		~Keyboard()                       = delete;
	};

	class Mouse {
	public:
		static Vec2i<size_t> position();
		static bool pressing(int);
		static bool pressed(int, int);
		static double scroll();
		static void cursor(int);
	private:
		friend Window;
		struct MouseEvent { int button, action, mods; };
		struct ScrollEvent { double xoffset, yoffset; };
		static inline std::vector<MouseEvent> mouse_events{};
		static inline std::vector<ScrollEvent> scroll_events{};
		Mouse()                        = delete;
		Mouse(const Mouse&)            = delete;
		Mouse(Mouse&&)                 = delete;
		void operator = (const Mouse&) = delete;
		void operator = (Mouse&&)      = delete;
		~Mouse()                       = delete;
	};

	class Window {
	public:
		static void create(const char*, int, int);
		static void destroy();
		static void vsync(bool);
		static bool isOpen();
		static void pollEvents();
		static void clear(Color color);
		static void draw(const Mesh&);
		static void draw(const Sprite&);
		static void draw(const Text&);
		static void display();
	private:
		static void callbackResize(GLFWwindow*, int, int);
		static void callbackKeyboard(GLFWwindow*, int, int, int, int);
		static void callbackMouse(GLFWwindow*, int, int, int);
		static void callbackScroll(GLFWwindow*, double, double);
		static inline unsigned int glslShaderProgramID{};
		Window()                        = delete;
		Window(const Window&)           = delete;
		Window(Window&&)                = delete;
		void operator = (const Window&) = delete;
		void operator = (Window&&)      = delete;
		~Window()                       = delete;
	};
}

