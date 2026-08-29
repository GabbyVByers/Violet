
/*
 *   Source File [main.cpp]
 */

#include "Violet.h"
#include <iostream>

//#define CAPTURE_EXCEPTIONS

int main() {
	#ifdef CAPTURE_EXCEPTIONS
	#ifndef EXIT_SUCCESS
	#define EXIT_SUCCESS 0
	#endif /* EXIT_SUCCESS */
	#ifndef EXIT_FAILURE
	#define EXIT_FAILURE 1
	#endif /* EXIT_FAILURE */
	try {
	#endif /* CAPTURE_EXCEPTIONS */
	
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
	}
	
	#ifdef CAPTURE_EXCEPTIONS
	} catch (const std::exception& error) {
		std::string message{ "Error: {}\n" };
		std::cerr << std::format(message, error.what());
		return EXIT_FAILURE;
	} catch (...) {
		std::cerr << "Unknown Error.\n";
		return EXIT_FAILURE;
	} return EXIT_SUCCESS;
	#endif
}

