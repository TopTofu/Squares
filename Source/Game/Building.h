#pragma once

#include "Engine/Mesh.h"
#include "Engine/Render.h"


enum class BuildingType{
	NONE = 0,
	ROAD = 1,
	APARTMENT = 2,
	SHOP = 3,
	SERVICE = 4
};

struct Building {
	Model model;

	BuildingType type = BuildingType::NONE;
};


void renderBuilding(Building& building, Camera& camera);

