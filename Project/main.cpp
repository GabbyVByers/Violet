
/*
 *   Source File [main.cpp]
 */

#include "Violet.h"
#include <iostream>

static void controlCamera();
static void testInput();

int main() {
	Vi::Window window{ "App Title", 1200, 700, true };
	window.vsync(false);

	Vi::Vertex vertices[] = {
		{ {-0.5,-0.4, 0 }, { 1, 0, 0, 1 }, { 0, 0 } },
		{ { 0.5,-0.4, 0 }, { 0, 1, 0, 1 }, { 0, 0 } },
		{ {   0, 0.4, 0 }, { 0, 0, 1, 1 }, { 0, 0 } },
	};

	Vi::Mesh mesh{};
	mesh.upload(vertices, 3);

	Vi::Camera::position.z = -1;

	while (window.isOpen()) {
		testInput();
		controlCamera();
		window.clear({ 0.1, 0, 0.1, 1 });
		window.draw(mesh);
		ImGui::ShowDemoWindow();
		window.display();
	} return EXIT_SUCCESS;
}

static void controlCamera() {

}

static void testInput() {
	if (Vi::Keyboard::pressing(SDL_SCANCODE_A)) { std::cout << "Holding 'A' Key!\n"; }
	if (Vi::Keyboard::pressed(SDL_SCANCODE_B)) { std::cout << "Pressed 'B' Key!\n"; }
	if (Vi::Keyboard::released(SDL_SCANCODE_B)) { std::cout << "Released 'B' Key!\n"; }

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

