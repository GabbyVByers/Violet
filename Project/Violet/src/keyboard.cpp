
/* keyboard.cpp */

#include "rendering.h"
#include <cassert>

namespace Vi {
	
	/* Public */

	bool Keyboard::pressed(int key, int action) {
		for (const KeyboardEvent& event : keyboard_events) {
			if ((key == event.key) && (action == event.action)) return true;
		} return false;
	}

	bool Keyboard::pressing(int key) {
		GLFWwindow* window = glfwGetCurrentContext();
		assert(window != nullptr);
		return (glfwGetKey(window, key) == GLFW_PRESS);
	}
}

