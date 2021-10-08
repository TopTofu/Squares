#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <Engine/Mesh.h>

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

	Mesh mesh;
};


World initWorld(int gridSize, float cellSize, GLuint shader);

Cell* cellAtWorldCoords(World& world, glm::vec3 coords);

void renderWorld(World& world, Camera& camera);
