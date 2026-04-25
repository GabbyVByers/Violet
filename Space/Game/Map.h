
/*
    Map.h
*/

#pragma once

#include "../../Violet/Violet.h"
#include "../../Violet/Siv.h"
#include "../../Violet/Socket.h"

#include <string>
#include <fstream>
#include <sstream>

class Planet {
public:
	Vi::ID id = Vi::InvalidID;
	std::string name = "Unnamed Planet";
	Vi::Vec3d position = Vi::Vec3d();
	Vi::Vec3d velocity = Vi::Vec3d();
};

class Map {
public:
	Map();
	void debug_gui() const;
	Vi::SiVector<Planet> planets{};
};

