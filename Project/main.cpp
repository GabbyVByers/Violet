
/*
 *   Source File [main.cpp]
 */

#include "Violet.h"
#include <iostream>

static void testMouse() {

	if (Vi::Mouse::pressing(SDL_BUTTON_MIDDLE)) {
		Vi::Vec2f pos = Vi::Mouse::position();
		std::cout << std::format("Mouse Position: ({}, {})\n", pos.x, pos.y);
	}

	if (Vi::Mouse::pressing(SDL_BUTTON_LEFT)) {
		Vi::Vec2f vel = Vi::Mouse::velocity();
		std::cout << std::format("Mouse Velocity: ({}, {})\n", vel.x, vel.y);
	}

	if (Vi::Mouse::pressed(SDL_BUTTON_RIGHT)) {
		std::cout << "Pressed Right Mouse Button!\n";
		Vi::Mouse::hide();
	}

	if (Vi::Mouse::released(SDL_BUTTON_RIGHT)) {
		std::cout << "Released Right Mouse Button!\n";
		Vi::Mouse::reveal();
	}

}

int main() {
	Vi::Window window{ "App Title", 0, 0 };
	window.vsync(true);

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

