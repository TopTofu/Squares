#pragma once

#include <vector>
#include <Game/Building.h>
#include <Game/World.h>

struct City {
	std::vector<Building> buildings;
};


extern City city;

void placeBuilding(Building& building, Cell& cell);

