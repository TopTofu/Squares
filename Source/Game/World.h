#pragma once

#include <glm/glm.hpp>
#include <vector>

struct Cell {
	glm::vec2 gridPosition;
	glm::vec3 worldPosition;
};


struct World {
	const glm::vec3 planeOrigin = { 0, 0, 0 };
	const glm::vec3 planeNormal = { 0, 1, 0 };

	int size;
	float cellSize;

	std::vector<Cell> grid;
};


World initWorld(int gridSize, float cellSize);

Cell* cellAtWorldCoords(World& world, glm::vec3 coords);

