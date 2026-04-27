
/*
    main.cpp
*/

#include "../../Violet/Violet.h"
#include "../../Violet/Siv.h"
#include "../../Violet/Socket.h"

#include "Game/Map.h"

static void udp_connection_test();
static void input_test(Vi::Window&);
static void control_camera(Vi::Camera&);

int main() {
    Vi::Window window = Vi::Window("Application Title", 1920, 1080);

	Vi::Mesh mesh = Vi::Shapes::sphere(1);
	Vi::Camera camera;
	camera.position = Vi::Vec3d(0, 0, 5);
	camera.fov_deg = 30.0;

	Map map;

    while (window.is_open()) {
        window.poll_events();
		window.clear(Vi::Color(0.1f, 0.1f, 0.2f));

		//input_test(window);
		control_camera(camera);
		udp_connection_test();

		//map.debug_gui();
		window.draw(mesh, camera);
		window.display();
    }

    return 0;
}

void udp_connection_test() {

	static Vi::SocketUDP udp_socket;

	ImGui::Begin("UDP Connection");
	static char ip_address[32] = "";
	static int port = 2000;
	ImGui::InputText("IP Address", ip_address, sizeof(ip_address));
	ImGui::InputInt("Port", &port);
	if (ImGui::Button("Listen on Port")) {
		udp_socket.set_listening_port(port);
	}
	if (ImGui::Button("Set Peer Address")) {
		udp_socket.set_destination_address(ip_address, port);
	}
	if (ImGui::Button("SEND")) {
		static const char* msg = "Hello friend!";
		udp_socket.send_packet(msg, (int)strlen(msg));
	}
	if (ImGui::Button("RECV")) {
		static char buffer[1024];
		int num_bytes = udp_socket.receive_packet(buffer, sizeof(buffer));
		if (num_bytes != INVALID_SOCKET) {
			std::string str(buffer, num_bytes);
			if (str == "")
				Vi::Log::info("No Packets");
			else
				Vi::Log::info("Received: " + str);
		}
	}
	ImGui::Text("Listening on Port: %d", (int)udp_socket.get_listening_port());
	ImGui::Text("Destination Address:");
	ImGui::Text("\tIP: %s", udp_socket.get_destination_address().c_str());
	ImGui::Text("\tPort: %d", (int)udp_socket.get_destination_port());
	ImGui::End();
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

void control_camera(Vi::Camera& camera) {

	const double speed = 0.001;
	static double distance = 2.5;
	Vi::Mouse& mouse = Vi::Window::mouse();

	{ /* remove me to disable the auto-spinning */
		Vi::Vec3d up = Vi::Vec3d::ypos();
		Vi::Quat rot_up = Vi::Quat::rotation(up, 20.0 * -speed);
		camera.orientation = rot_up * camera.orientation;
		camera.orientation = camera.orientation.normalized();
		camera.position = camera.forward() * (-distance);
		//return;
	}

	if (mouse.imgui_captured())
		return;

	if (mouse.pressing(GLFW_MOUSE_BUTTON_LEFT)) {
		Vi::Vec3d up = Vi::Vec3d::ypos();
		Vi::Quat rot_up = Vi::Quat::rotation(up, (double)mouse.velocity().x * -speed);
		camera.orientation = rot_up * camera.orientation;
		Vi::Vec3d right = camera.right();
		Vi::Quat rot_right = Vi::Quat::rotation(right, (double)mouse.velocity().y * -speed);
		camera.orientation = rot_right * camera.orientation;
		camera.orientation = camera.orientation.normalized();
	}

	double scroll = mouse.scroll();
	if (scroll != 0) {
		distance *= (45.0 - scroll) / 45.0;
	}

	camera.position = camera.forward() * (-distance);
}

