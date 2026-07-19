
/* window.cpp */

#include "rendering.h"
#include <cassert>

namespace Vi {

	/* Public */

	void Window::create(const char* title, int width, int height) {
		GLFWwindow* window = glfwGetCurrentContext();
		assert(window == nullptr);
		
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		glfwMakeContextCurrent(window);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		
		glViewport(0, 0, width, height);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_PROGRAM_POINT_SIZE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glfwSetFramebufferSizeCallback(window, callbackResize);
		glfwSetKeyCallback(window, callbackKeyboard);
		glfwSetMouseButtonCallback(window, callbackMouse);
		glfwSetScrollCallback(window, callbackScroll);
	}

	void Window::destroy() {
		GLFWwindow* window = glfwGetCurrentContext();
		assert(window != nullptr);
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	bool Window::isOpen() {
		GLFWwindow* window = glfwGetCurrentContext();
		assert(window != nullptr);
		return !glfwWindowShouldClose(window);
	}

	void Window::pollEvents() {
		Mouse::mouse_events.clear();
		Mouse::scroll_events.clear();
		Keyboard::keyboard_events.clear();
		glfwPollEvents();
	}

	void Window::clear(Color color) {
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::draw(const Mesh& mesh) {
		glUseProgram(glslShaderProgramID); // move to constructor? (won't change @ each call)
		
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, mesh.glTextureID);
	}

	void Window::draw(const Sprite& sprite) {

	}

	void Window::draw(const Text& text) {

	}

	/* Private */

	void Window::display() {
		GLFWwindow* window = glfwGetCurrentContext();
		assert(window != nullptr);
		glfwSwapBuffers(window);
	}

	/* Callbacks */

	void Window::callbackResize(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	void Window::callbackKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
		Keyboard::KeyboardEvent event = {
			.key = key,
			.scancode = scancode,
			.action = action,
			.mods = mods
		};
		Keyboard::keyboard_events.push_back(event);
	}

	void Window::callbackMouse(GLFWwindow* window, int button, int action, int mods) {
		Mouse::MouseEvent event = {
			.button = button,
			.action = action,
			.mods = mods
		};
		Mouse::mouse_events.push_back(event);
	}

	void Window::callbackScroll(GLFWwindow* window, double xoffset, double yoffset) {
		Mouse::ScrollEvent event = {
			.xoffset = xoffset,
			.yoffset = yoffset,
		};
		Mouse::scroll_events.push_back(event);
	}
}

