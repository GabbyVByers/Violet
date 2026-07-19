
/* demo.cpp */

#include "rendering.h"

static void inputTest();

int main() {	
	Vi::Window::create("Hello OpenGL", 500, 500);

	while (Vi::Window::isOpen()) {
		Vi::Window::pollEvents();
		Vi::Window::clear(Vi::Color::blue());
		inputTest();
		//Vi::Window::draw();
		Vi::Window::display();
	}

	Vi::Window::destroy();
	return 0;
}

void inputTest() {

	/* Mouse */

	if (Vi::Mouse::pressing(GLFW_MOUSE_BUTTON_RIGHT)) {
		std::cout << "Holding Right Mouse Button\n";
	}

	if (Vi::Mouse::pressed(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS)) {
		std::cout << "Left Mouse Button Pressed\n";
	}

	if (Vi::Mouse::pressed(GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE)) {
		std::cout << "Left Mouse Button Released\n";
	}

	/* Keyboard */

	if (Vi::Keyboard::pressing(GLFW_KEY_M)) {
		Vi::Vec2<int> pos = Vi::Mouse::position();
		std::cout << "(x: " << pos.x << ", y: " << pos.y << ")\n";
	}
	
	if (Vi::Keyboard::pressing(GLFW_KEY_Q)) {
		std::cout << "Holding Q\n";
	}

	if (Vi::Keyboard::pressed(GLFW_KEY_W, GLFW_PRESS)) {
		std::cout << "Pressed W\n";
	}
	
	if (Vi::Keyboard::pressed(GLFW_KEY_W, GLFW_RELEASE)) {
		std::cout << "Released W\n";
	}
}

