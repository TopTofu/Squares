#pragma once

#include <glm/glm.hpp>

#include <Engine/Mesh.h>
#include <Engine/Render.h>
#include <Game/Building.h>

#include <vector>
#include <algorithm>

struct Cell {
	glm::vec2 gridPosition;
	glm::vec3 worldPosition;

	bool occupied = false;

	Building occupant;
};


struct WorldInfo {
	const glm::vec3 planeOrigin = { 0, 0, 0 };
	const glm::vec3 planeNormal = { 0, 1, 0 };

	int size;
	float cellSize;

	std::vector<Cell> grid;

	Mesh mesh;

	bool initialized = false;
};

extern WorldInfo World;


void initWorld(int gridSize, float cellSize, GLuint shader);

void renderWorld(Camera& camera);

Cell* cellAtWorldCoords(glm::vec3 coords);
void placeBuilding(Building& building, glm::vec3 coords);