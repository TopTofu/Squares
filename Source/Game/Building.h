#pragma once

#include <Engine/Mesh.h>
#include <Engine/Render.h>


struct Building {
	Model model;
};


void renderBuilding(Building& building, Camera& camera);

