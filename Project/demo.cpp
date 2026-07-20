
/****************/
/*   demo.cpp   */
/****************/

#include "rendering.h"

static void inputTest();

int main() {	
	Vi::Window::create("Title", 500, 500);

	Vi::Mesh mesh{};
	mesh.vertices.push_back({ Vi::Vec3<float>{0, 0, 0}, {}, Vi::Color::red() });
	mesh.vertices.push_back({ Vi::Vec3<float>{1, 0, 0}, {}, Vi::Color::red() });
	mesh.vertices.push_back({ Vi::Vec3<float>{0, 1, 0}, {}, Vi::Color::red() });

	Vi::Camera::position = Vi::Vec3<double>{ 0, 0, 5 };

	while (Vi::Window::isOpen()) {
		Vi::Window::pollEvents();
		Vi::Window::clear(Vi::Color::blue());
		Vi::Window::draw(mesh);
		inputTest();
		Vi::Window::display();
	}

	Vi::Window::destroy();
	return 0;
}

void inputTest() {
	if (Vi::Mouse::pressing(GLFW_MOUSE_BUTTON_RIGHT)) { std::cout << "Holding Right Mouse Button\n"; }
	if (Vi::Mouse::pressed(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS)) { std::cout << "Left Mouse Button Pressed\n"; }
	if (Vi::Mouse::pressed(GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE)) { std::cout << "Left Mouse Button Released\n"; }
	if (Vi::Keyboard::pressing(GLFW_KEY_Q)) {std::cout << "Holding Q\n"; }
	if (Vi::Keyboard::pressed(GLFW_KEY_W, GLFW_PRESS)) { std::cout << "Pressed W\n"; }
	if (Vi::Keyboard::pressed(GLFW_KEY_W, GLFW_RELEASE)) {std::cout << "Released W\n"; }

	if (Vi::Keyboard::pressing(GLFW_KEY_M)) {
		Vi::Vec2i<size_t> pos = Vi::Mouse::position();
		std::cout << "(x: " << pos.x << ", y: " << pos.y << ")\n";
	}
}

