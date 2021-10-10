#pragma once

#include <Engine/Mesh.h>
#include <Engine/Render.h>


struct Building {
	Model* model;

	glm::vec2 gridPosition;
};


void renderBuilding(Building& building, Camera& camera);

