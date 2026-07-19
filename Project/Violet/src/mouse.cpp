
/* mouse.cpp */

#include "rendering.h"

namespace Vi {
	
	/* Public */

	Vec2i<int> Mouse::position() {
		GLFWwindow* window = glfwGetCurrentContext();
		assert(window != nullptr);
		double x, y; glfwGetCursorPos(window, &x, &y);
		return Vec2i<int>{(int)x, (int)y};
	}

	bool Mouse::pressing(int button) {
		GLFWwindow* window = glfwGetCurrentContext();
		assert(window != nullptr);
		return glfwGetMouseButton(window, button) == GLFW_PRESS;
	}

	bool Mouse::pressed(int button, int action) {
		for (const MouseEvent& event : mouse_events) {
			if ((button == event.button) && (action == event.action)) return true;
		} return false;
	}

	double Mouse::scroll() {
		double scroll{};
		for (const ScrollEvent& event : scroll_events) {
			scroll += event.yoffset;
		} return scroll;
	}

	void Mouse::cursor(int setting) {
		/**********************/
		/* GLFW_CURSOR_NORMAL */
		/* GLFW_CURSOR_HIDDEN */
		/**********************/
		GLFWwindow* window = glfwGetCurrentContext();
		assert(window != nullptr);
		glfwSetInputMode(window, GLFW_CURSOR, setting);
	}
}

