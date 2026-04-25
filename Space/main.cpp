
/*
    main.cpp
*/

#include "../Violet/Violet.h"
//#include "../Violet/Siv.h"
#include "../Violet/Socket.h"

#include <string>
#include <fstream>
#include <sstream>

class Planet {
public:
	//Vi::ID id = Vi::InvalidID;
	std::string name = "Unnamed Planet";
	Vi::Vec3d position = Vi::Vec3d();
	Vi::Vec3d velocity = Vi::Vec3d();
};

class Map {
public:

	Map() {
		const std::string path = "Space/orbital_parameters.txt";
		std::ifstream file(path);
		if (!file) {
			Vi::Log::error("Could not open " + path);
			std::terminate();
		}

		std::stringstream sstream;
		sstream << file.rdbuf();
		file.close();

		std::string token;
		while (sstream >> token) {
			if (token == "Begin_Planets") {
				while (sstream >> token) {
					if (token == "End_Planets")
						break;
					Planet planet;
					planet.name = token;
					sstream >> token; if (token != "X") { Vi::Log::warning("Expected 'X' (" + token + ")"); }
					sstream >> planet.position.x;
					sstream >> token; if (token != "Y") { Vi::Log::warning("Expected 'Y' (" + token + ")"); }
					sstream >> planet.position.y;
					sstream >> token; if (token != "Z") { Vi::Log::warning("Expected 'Z' (" + token + ")"); }
					sstream >> planet.position.z;
					sstream >> token; if (token != "VX") { Vi::Log::warning("Expected 'VX' (" + token + ")"); }
					sstream >> planet.velocity.x;
					sstream >> token; if (token != "VY") { Vi::Log::warning("Expected 'VY' (" + token + ")"); }
					sstream >> planet.velocity.y;
					sstream >> token; if (token != "VZ") { Vi::Log::warning("Expected 'VZ' (" + token + ")"); }
					sstream >> planet.velocity.z;
					planets.push_back(planet);
				}
			}
			if (token == "End_Moons") {
				break;
			}
			sstream >> token;
			if (token != "Begin_Moons") { Vi::Log::warning("Expected 'Begin_Moons' (" + token + ")"); }
			while (sstream >> token) {
				if (token == "End_Moons")
					break;
			}
		}
	}

	//Vi::SiVector<Planet> planets;
	std::vector<Planet> planets;

};

static void udp_connection_test();
static void input_test(Vi::Window&);
static void control_camera(Vi::Camera&);

int main() {
	Vi::WinSock::init();
    Vi::Window window = Vi::Window("Application Title", 1920, 1080);

	Vi::Mesh mesh = Vi::Shapes::sphere(10);
	Vi::Camera camera;
	camera.position = Vi::Vec3d(0, 0, 5);

	Map map;

    while (window.is_open()) {
        window.poll_events();
		window.clear(Vi::Color(0.1f, 0.1f, 0.2f));

		//input_test(window);
		control_camera(camera);

		udp_connection_test();

		//ImGui::Begin("Debug");
		//for (size_t i = 0; i < map.planets.size(); i++) {
		//	const Planet& planet = map.planets[i];
		//	ImGui::Text(planet.name.c_str());
		//	Vi::Vec3f pos = static_cast<Vi::Vec3f>(planet.position);
		//	Vi::Vec3f vel = static_cast<Vi::Vec3f>(planet.velocity);
		//	std::string pos_label = "Position##" + std::to_string(i);
		//	std::string vel_label = "Velocity##" + std::to_string(i);
		//	ImGui::InputFloat3(pos_label.c_str(), (float*)&pos);
		//	ImGui::InputFloat3(vel_label.c_str(), (float*)&vel);
		//}
		//ImGui::End();
		
		window.draw(mesh, camera);
		window.display();
    }

	Vi::WinSock::cleanup();
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
		udp_socket.set_peer_address(ip_address, port);
	}
	if (ImGui::Button("SEND")) {
		static const char* msg = "Hello friend!";
		udp_socket.send_packet(msg, strlen(msg));
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
	ImGui::Text("\tIP: %s", udp_socket.get_peer_address().c_str());
	ImGui::Text("\tPort: %d", (int)udp_socket.get_peer_port());
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

	{
		Vi::Vec3d up = Vi::Vec3d::ypos();
		Vi::Quat rot_up = Vi::Quat::rotation(up, 20.0 * -speed);
		camera.orientation = rot_up * camera.orientation;
		camera.orientation = camera.orientation.normalized();
		camera.position = camera.forward() * (-distance);
		return;
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

 