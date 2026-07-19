
/* rendering.h */

#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb/stb_image.h"

#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "vec2.h"
#include "vec3.h"

#ifndef Vi
#define Vi Vi
#endif /* Vi */

namespace Vi {
	
	class Quaternion {};

	/***************************************************/
	/*     Color, Vertex, Mesh, Sprite, Text, Lines     */
	/***************************************************/
	
	class Color {
	public:
		static Color white() { return Color{1.f, 1.f, 1.f, 1.f}; }
		static Color black() { return Color{0.f, 0.f, 0.f, 1.f}; }
		static Color red()   { return Color{1.f, 0.f, 0.f, 1.f}; }
		static Color green() { return Color{0.f, 1.f, 0.f, 1.f}; }
		static Color blue()  { return Color{0.f, 0.f, 1.f, 1.f}; }
		float r{1.f}, g{1.f}, b{1.f}, a{1.f};
	};

	class Vertex {
	public:
		Vec3<float> position{};
		Vec2<float> texCoord{};
		Color color{};
	};

	class Image {
	public:
		Image(const Vec2i<int>& = Vec2i<int>{1, 1}); /* User Created */
		Image(const char*);                          /* Loaded From File */
		int width() const;
		int height() const;
		Color getPixel(const Vec2i<int>&) const;
		void setPixel(const Vec2i<int>&, const Color&);
	private:
		Vec2i<int> size{};
		std::unique_ptr<unsigned char[]> pixels{};
	};

	class Texture {
	public:
	private:
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

	class Lines {
	public:
	private:
	};

	/***************************************************/
	/*             Keyboard, Mouse, Window             */
	/***************************************************/

	class Window; /* Fwrd Dec */

	class Keyboard {
	public:
		static bool pressed(int, int);
		static bool pressing(int);
	private:
		friend Window;
		struct KeyboardEvent { int key, scancode, action, mods; };
		static inline std::vector<KeyboardEvent> keyboard_events{};
		Keyboard()                        = delete;
		~Keyboard()                       = delete;
		Keyboard(const Keyboard&)         = delete;
		Keyboard(Keyboard&&)              = delete;
		void operator = (const Keyboard&) = delete;
		void operator = (Keyboard&&)      = delete;
	};

	class Mouse {
	public:
		static Vec2i<int> position();
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
		~Mouse()                       = delete;
		Mouse(const Mouse&)            = delete;
		Mouse(Mouse&&)                 = delete;
		void operator = (const Mouse&) = delete;
		void operator = (Mouse&&)      = delete;
	};

	class Window {
	public:
		static void create(const char*, int, int);
		static void destroy();
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
		~Window()                       = delete;
		Window(const Window&)           = delete;
		Window(Window&&)                = delete;
		void operator = (const Window&) = delete;
		void operator = (Window&&)      = delete;
	};
}

