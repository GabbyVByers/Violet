
/*
    main.cpp
*/

#include "../Header/Violet.h"

static void input_test(Vi::Window& window);

int main() {
    
    Vi::Window window = Vi::Window("Application Title", 1920, 1080);

	Vi::Mesh mesh;
	Vi::Camera camera;

    while (window.is_open()) {
        window.poll_events();
		window.clear(Vi::Color(0.1, 0.1, 0.2));
		window.draw(mesh, camera);
		window.display();
		input_test(window);
    }

    return 0;
}

void input_test(Vi::Window& window) {
	Vi::Mouse& mouse = Vi::Window::mouse();
	Vi::Keyboard& keyboard = Vi::Window::keyboard();

	if (mouse.clicked(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS))
		std::cout << "Left Mouse Button Pressed\n";
	if (mouse.clicked(GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE))
		std::cout << "Left Mouse Button Released\n";
	if (mouse.clicked(GLFW_MOUSE_BUTTON_RIGHT, GLFW_PRESS))
		std::cout << "Right Mouse Button Pressed\n";
	if (mouse.clicked(GLFW_MOUSE_BUTTON_RIGHT, GLFW_RELEASE))
		std::cout << "Right Mouse Button Released\n";
	if (mouse.clicked(GLFW_MOUSE_BUTTON_MIDDLE, GLFW_PRESS))
		std::cout << "Middle Mouse Button Pressed\n";
	if (mouse.clicked(GLFW_MOUSE_BUTTON_MIDDLE, GLFW_RELEASE))
		std::cout << "Middle Mouse Button Released\n";

	double scroll = mouse.scroll();
	if (scroll > 0.0)
		std::cout << "Scrolled Up: scroll = " << scroll << "\n";
	if (scroll < 0.0)
		std::cout << "Scrolled Down: scroll = " << scroll << "\n";

	if (keyboard.pressing(GLFW_KEY_SPACE)) {
		Vi::Vec2d pos = mouse.position();
		std::cout << "Cursor Position: x = " << pos.x << " y = " << pos.y << "\n";
	}
	if (keyboard.pressing(GLFW_KEY_LEFT_SHIFT)) {
		Vi::Vec2d vel = mouse.velocity();
		if ((vel.x != 0.0) || (vel.y != 0.0))
			std::cout << "Cursor Velocity: x = " << vel.x << " y = " << vel.y << "\n";
	}

	if (keyboard.pressed(GLFW_KEY_W, GLFW_PRESS))
		std::cout << "W key Pressed\n";
	if (keyboard.pressed(GLFW_KEY_W, GLFW_RELEASE))
		std::cout << "W key Released\n";
	if (keyboard.pressing(GLFW_KEY_A))
		std::cout << "A Button Being Held Down\n";
	if (keyboard.pressing(GLFW_KEY_S)) {
		Vi::Vec2i size = window.size();
		std::cout << "Window Size: " << size.x << " " << size.y << "\n";
	}
}

