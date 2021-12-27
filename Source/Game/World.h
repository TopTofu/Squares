#pragma once

#include <glm/glm.hpp>

#include "Engine/Mesh.h"
#include "Engine/Render.h"
#include "Game/Building.h"

#include <vector>
#include <algorithm>

struct Cell {
	glm::vec3 gridPosition;
	glm::vec3 worldPosition;

	Cell* above = 0;
	Cell* below = 0;

	bool occupied = false;
};


struct CityInfo {
	std::map<Building, std::vector<Cell*>> placedBuildings;
	// @todo future container for stats like population, income, happiness...
};


struct WorldInfo {
	const glm::vec3 planeOrigin = { 0, 0, 0 };
	const glm::vec3 planeNormal = { 0, 1, 0 };
	
	glm::vec3 dimensions;
	float cellSize;

	std::vector<Cell> grid;

	Mesh mesh;

	bool initialized = false;
};

extern WorldInfo* World;
extern CityInfo* City;


void initWorld(glm::vec3 dimensions, float cellSize, GLuint shader);

void renderWorld(Camera& camera);

Cell* cellAtWorldCoords(glm::vec3 coords); 
Cell* cellAtGridCoords(glm::vec3 coords);

glm::vec3 worldToGridCoords(glm::vec3 worldCoords);

void placeBuildingAtWorldCoords(Building& building, glm::vec3 worldCoords, bool force = false);
void placeBuildingAtGridCoords(Building& building, glm::vec3 gridCoords, bool force = false);

void removeBuildingAtGridCoords(glm::vec3 gridCoords);
void removeBuildingAtWorldCoords(glm::vec3 worldCoords);

int gridIndex(glm::vec3 gridCoords);

