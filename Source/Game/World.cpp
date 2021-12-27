#include <Game/World.h>

WorldInfo* World;
CityInfo* City;

void initWorld(glm::vec3 dimensions, float cellSize, GLuint shader) {
	World = new WorldInfo;
	City = new CityInfo;

	World->dimensions = dimensions;
	World->cellSize = cellSize;

	for (int z = 0; z < dimensions.z; z++) {
		for (int y = 0; y < dimensions.y; y++) {
			for (int x = 0; x < dimensions.x; x++) {
				Cell c;
				c.gridPosition = { x, y, z };
				c.worldPosition = { x * cellSize, z * cellSize, y * cellSize };

				World->grid.push_back(c);
			}
		}
	}

	for (int z = 0; z < dimensions.z; z++) {
		for (int y = 0; y < dimensions.y; y++) {
			for (int x = 0; x < dimensions.x; x++) {
				Cell* c = &World->grid[gridIndex({ x, y, z })];
				if (z > 0)
					c->below = &World->grid[gridIndex({ x, y, z - 1 })];
				if (z < dimensions.z - 1)
					c->above = &World->grid[gridIndex({ x, y, z + 1 })];
			}
		}
	}

	World->mesh = getQuadMesh({ 0, 0, 0 }, { cellSize * dimensions.x, 0, 0 }, { 0, 0, cellSize * dimensions.y }, { 0.09f, 0.34f, 0.23f, 1.0f });
	World->mesh.shader = shader;

	World->initialized = true;
}

void renderWorld(Camera& camera) {
	renderMesh(World->mesh, camera);

	for (auto pair : City->placedBuildings) {
		Building b = pair.first;
		renderBuilding(b, camera);
	}
}

Cell* cellAtWorldCoords(glm::vec3 coords) {
	int index = gridIndex(worldToGridCoords(coords));

	if (index > World->grid.size() - 1) {
		// @temporary this should not be happening
		printf("Requested Cell at x=%, y=%, z=% which is outside of the grid", coords.x, coords.z, coords.y);
		return 0;
	}

	Cell* c = &World->grid[index];
	return c;
}

Cell* cellAtGridCoords(glm::vec3 coords) {
	int index = gridIndex(coords);
	if (index > World->grid.size() - 1)
		return 0;
	return &World->grid[index];
}

glm::vec3 worldToGridCoords(glm::vec3 worldCoords) {
	// world y is up while grid z is up
	int gridX = worldCoords.x / World->cellSize;
	int gridY = worldCoords.z / World->cellSize;
	int gridZ = worldCoords.y / World->cellSize;

	gridX = std::clamp(gridX, 0, (int)World->dimensions.x - 1);
	gridY = std::clamp(gridY, 0, (int)World->dimensions.y - 1);
	gridZ = std::clamp(gridZ, 0, (int)World->dimensions.z - 1);

	return { gridX, gridY, gridZ };
}

void placeBuildingAtWorldCoords(Building& building, glm::vec3 worldCoords, bool force) {
	placeBuildingAtGridCoords(building, worldToGridCoords(worldCoords), force);
}

// ----------------------------------
// TODO fix rendering (render city instead of cells)
// ----------------------------------

// @temporary quick building id solution
static int buildingID = 0;

void placeBuildingAtGridCoords(Building& building, glm::vec3 gridCoords, bool force) {
	Cell* cell = cellAtGridCoords(gridCoords);
	std::vector<Cell*> affectedCells = { cell };
	glm::vec3 cellPos = cell->gridPosition;

	if (cell->occupied && !force) {
		return;
	}

	for (int x = 1; x < building.xSize; x++) {
		Cell* c = cellAtGridCoords(cellPos + glm::vec3{ -x, 0, 0 });
		if ((!c || c->occupied) && !force) {
			// @todo this is the place to inform the player there is something in the way
			return;
		}
		affectedCells.push_back(c);
	}

	for (int y = 1; y < building.ySize; y++) {
		Cell* c = cellAtGridCoords(cellPos + glm::vec3{ 0, -y, 0 });
		if ((!c || c->occupied) && !force) {
			// @todo this is the place to inform the player there is something in the way
			return;
		}
		affectedCells.push_back(c);
	}

	Building b = building;
	glm::vec3 offset = {};
	if (b.type == BuildingType::ROAD) {
		offset = glm::vec3(0.5 * World->cellSize, 0, 0.5 * World->cellSize);
	}
	b.model.translation = cell->worldPosition + offset;
	b.id = ++buildingID;
	for (Cell* cell : affectedCells) {
		cell->occupied = true;
	}
	City->placedBuildings.emplace(b, affectedCells);
}

void removeBuildingAtGridCoords(glm::vec3 gridCoords) {
	Cell* cell = &World->grid[gridIndex(gridCoords)];
	if (!cell->occupied)
		return;

	for (auto pair : City->placedBuildings) {
		// find map item with cell (and subsequent building)
		if (std::find(pair.second.begin(), pair.second.end(), cell) != pair.second.end()) {
			for (Cell* c : pair.second) {
				c->occupied = false;
			}
			City->placedBuildings.erase(pair.first);
			return;
		}
	}
}

void removeBuildingAtWorldCoords(glm::vec3 worldCoords) {
	removeBuildingAtGridCoords(worldToGridCoords(worldCoords));
}

int gridIndex(glm::vec3 gridCoords) {
	return gridCoords.x + gridCoords.y * World->dimensions.x + gridCoords.z * World->dimensions.x * World->dimensions.y;
}