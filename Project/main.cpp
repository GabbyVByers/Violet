
/*
 *   Source File [main.cpp]
 */

#include "Violet.h"
#include <iostream>

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
		window.clear({ 0.1, 0, 0.1, 1 });
		window.draw(mesh);
		window.display();
	} return EXIT_SUCCESS;
}

