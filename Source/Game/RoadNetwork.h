#pragma once

#include <vector>

#include <glm/glm.hpp>

#include <Game/World.h>

/*
		N
	y+	^
		|
   W <--+--> E
		|	x+
		v
		S

*/

enum class RoadDirectionFlag {
	Placed = 1 << 0,
	North = 1 << 1,
	East = 1 << 2,
	South = 1 << 3,
	West = 1 << 4,
};

struct RoadNetworkInfo {
	std::vector<int> roads;
};

extern RoadNetworkInfo RoadNetwork;

void initRoadNetwork();

void addRoad(glm::vec3 gridPosition);
void updateRoadMeshInCell(glm::vec3 gridPosition);
void printNetwork();