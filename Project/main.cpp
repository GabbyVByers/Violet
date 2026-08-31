
/*
 *   Source File [main.cpp]
 */

#include "Violet.h"
#include <iostream>

static void testMouse() {

	if (Vi::Mouse::pressing(SDL_BUTTON_LEFT)) {
		std::cout << "Holding Left Mouse Button!\n";
	}

	if (Vi::Mouse::pressed(SDL_BUTTON_RIGHT)) {
		std::cout << "Pressed Right Mouse Button!\n";
	}

	if (Vi::Mouse::released(SDL_BUTTON_RIGHT)) {
		std::cout << "Released Right Mouse Button!\n";
	}

}

int main() {
	Vi::Window window{ "App Title", 0, 0 };
	window.vsync(false);

	Vi::Matrix x{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1,
	};

	Vi::Vertex vertices[] = {
		{ {-0.5,-0.4, 0 }, { 1, 0, 0, 1 }, { 0, 0 } },
		{ { 0.5,-0.4, 0 }, { 0, 1, 0, 1 }, { 0, 0 } },
		{ {   0, 0.4, 0 }, { 0, 0, 1, 1 }, { 0, 0 } },
	};

	Vi::Mesh mesh{};
	mesh.upload(vertices, 3);

	Vi::Camera::position.z = -1;

	while (window.isOpen()) {
		testMouse();
		window.clear({ 0.1, 0, 0.1, 1 });
		window.draw(mesh);
		window.display();
	} return EXIT_SUCCESS;
}

