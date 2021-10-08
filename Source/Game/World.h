#pragma once

#include <glm/glm.hpp>

#include <Engine/Mesh.h>
#include <Engine/Render.h>

#include <vector>
#include <algorithm>

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

	bool initialized = false;
};

extern World world;


void initWorld(int gridSize, float cellSize, GLuint shader);

Cell* cellAtWorldCoords(glm::vec3 coords);

void renderWorld(Camera& camera);
