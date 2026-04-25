
/*
    Map.cpp
*/

#include "Map.h"

Map::Map() {
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

void Map::debug_gui() const {
	ImGui::Begin("Debug");
	for (size_t i = 0; i < planets.size(); i++) {
		const Planet& planet = planets[i];
		ImGui::Text(planet.name.c_str());
		Vi::Vec3f pos = static_cast<Vi::Vec3f>(planet.position);
		Vi::Vec3f vel = static_cast<Vi::Vec3f>(planet.velocity);
		std::string pos_label = "Position##" + std::to_string(i);
		std::string vel_label = "Velocity##" + std::to_string(i);
		ImGui::InputFloat3(pos_label.c_str(), (float*)&pos);
		ImGui::InputFloat3(vel_label.c_str(), (float*)&vel);
	}
	ImGui::End();
}

