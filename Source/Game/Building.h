#pragma once

#include "Engine/Mesh.h"
#include "Engine/Render.h"
#include "Util/Utilities.h"


enum class BuildingType{
	NONE = 0,
	ROAD = 1,
	APARTMENT = 2,
	SHOP = 3,
	SERVICE = 4
};

struct Building {
	int id;

	Model model;

	BuildingType type = BuildingType::NONE;

	int xSize;
	int ySize;

	bool operator<(const Building& o) const {
		return id < o.id;
	}

	bool operator==(const Building& o) const {
		return id == o.id;
	}
};

struct BuildingCatalogInfo {
	std::map<std::string, Building> buildings = {};
};

extern BuildingCatalogInfo BuildingCatalog;

void initBuildingCatalog(std::string catalogFilePath);
Building getBuildingFromCatalog(std::string name);
void renderBuilding(Building& building, Camera& camera);
