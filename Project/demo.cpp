
/****************/
/*   demo.cpp   */
/****************/

#include "rendering.h"

static void controlCamera();
static void worldAxies();
static void inputTest();

int main() {	
	Vi::Window::create("Title", 500, 500);
	Vi::Window::vsync(true);

	Vi::Mesh mesh{};
	mesh.vertices.push_back({ {0, 0, 0}, {0, 0}, {} });
	mesh.vertices.push_back({ {1, 0, 0}, {2, 0}, {} });
	mesh.vertices.push_back({ {0, 1, 0}, {0, 2}, {} });
	mesh.vertices.push_back({ {1, 0, 0}, {2, 0}, {} });
	mesh.vertices.push_back({ {0, 1, 0}, {0, 2}, {} });
	mesh.vertices.push_back({ {1, 1, 0}, {2, 2}, {} });
	mesh.glPrimitiveType = GL_TRIANGLES;
	
	Vi::Image tulips{"Textures/tulips.png"};
	mesh.texture = Vi::Texture(tulips);

	Vi::Camera::position = Vi::Vec3<double>{1, 1, 5};

	Vi::Sprite sprite(tulips);
	sprite.size = { 50,50 };

	while (Vi::Window::isOpen()) {
		Vi::Window::pollEvents();
		Vi::Window::clear(Vi::Color{0.5, 0.5, 1.0, 1.0});
		controlCamera();

		sprite.position = Vi::Mouse::position();

		mesh.rotate(Vi::Vec3<double>::ypos(), 0.1);

		worldAxies();
		Vi::Window::draw(mesh);
		Vi::Window::draw(sprite);
		
		inputTest();
		ImGui::Begin("A gui!", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
		ImGui::Text("Some text!");
		ImGui::End();
		
		Vi::Window::display();
	}

	Vi::Window::destroy();
	return 0;
}

void controlCamera() {
	constexpr double speed{0.05};

	Vi::Vec3<double> forward = Vi::Camera::forward();
	forward.y = 0.0;
	forward.normalize();
	if (Vi::Keyboard::pressing(GLFW_KEY_W))          { Vi::Camera::position += forward * speed; }
	if (Vi::Keyboard::pressing(GLFW_KEY_A))          { Vi::Camera::position += Vi::Camera::right() * -speed; }
	if (Vi::Keyboard::pressing(GLFW_KEY_S))          { Vi::Camera::position += forward * -speed; }
	if (Vi::Keyboard::pressing(GLFW_KEY_D))          { Vi::Camera::position += Vi::Camera::right() * speed; }
	if (Vi::Keyboard::pressing(GLFW_KEY_SPACE))      { Vi::Camera::position += static_cast<Vi::Vec3<double>>(Vi::Vec3<double>::ypos()) * speed; }
	if (Vi::Keyboard::pressing(GLFW_KEY_LEFT_SHIFT)) { Vi::Camera::position += static_cast<Vi::Vec3<double>>(Vi::Vec3<double>::yneg()) * speed; }

	//if (Vi::Mouse::pressed(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS))   { Vi::Mouse::cursor(GLFW_CURSOR_DISABLED); }
	//if (Vi::Mouse::pressed(GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE)) { Vi::Mouse::cursor(GLFW_CURSOR_NORMAL); }
	//if (Vi::Mouse::pressing(GLFW_MOUSE_BUTTON_LEFT)) {
	//	double sensitivity{0.05};
	//	double x_movement = mouse.velocity().x;
	//	double y_movement = mouse.velocity().y;
	//	// Lateral Rotation
	//	Vi::Vec3<double> up = Vi::Vec3<double>::ypos();
	//	Vi::Quat lateral_rotation = Vi::Quat::rotation(up, sensitivity * -x_movement);
	//	camera.orientation = lateral_rotation * camera.orientation;
	//	// Longitudinal Rotation
	//	Vi::Vec3<double> right = camera.right();
	//	Vi::Quat longitudinal_rotation = Vi::Quat::rotation(right, sensitivity * -y_movement);
	//	camera.orientation = longitudinal_rotation * camera.orientation;
	//	camera.orientation = camera.orientation.normalized();
	//}
}

void worldAxies() {
	static Vi::Mesh axies{};
	if (axies.vertices.size() == 0) {
		axies.glPrimitiveType = GL_LINES;
		axies.vertices.push_back({ { 5, 0, 0 }, {}, Vi::Color::red() });
		axies.vertices.push_back({ {-5, 0, 0 }, {}, Vi::Color::red() });
		axies.vertices.push_back({ { 0, 5, 0 }, {}, Vi::Color::green() });
		axies.vertices.push_back({ { 0,-5, 0 }, {}, Vi::Color::green() });
		axies.vertices.push_back({ { 0, 0, 5 }, {}, Vi::Color::blue() });
		axies.vertices.push_back({ { 0, 0,-5 }, {}, Vi::Color::blue() });
	} Vi::Window::draw(axies);
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

