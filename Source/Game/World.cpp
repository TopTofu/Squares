#include <Game/World.h>

WorldInfo World;

void initWorld(glm::vec3 dimensions, float cellSize, GLuint shader) {
	if (World.initialized) {
		printf("World Struct has already been initialized!");
		return;
	}

	for (int z = 0; z < dimensions.z; z++) {
		for (int y = 0; y < dimensions.y; y++) {
			for (int x = 0; x < dimensions.x; x++) {
				Cell c;
				c.gridPosition = { x, y, z };
				c.worldPosition = { x * cellSize, 0, y * cellSize };

				World.grid.push_back(c);
			}
		}
	}

	World.dimensions = dimensions;
	World.cellSize = cellSize;

	World.mesh = getQuadMesh({ 0, 0, 0 }, { cellSize * dimensions.x, 0, 0 }, { 0, 0, cellSize * dimensions.y }, { 0.09f, 0.34f, 0.23f, 1.0f });
	World.mesh.shader = shader;

	World.initialized = true;
}

void renderWorld(Camera& camera) {
	renderMesh(World.mesh, camera);

	for (Cell& cell : World.grid) {
		if (cell.occupied)
			renderBuilding(cell.occupant, camera);
	}
}

Cell* cellAtWorldCoords(glm::vec3 coords) {
	// world y is up while grid z is up
	int gridX = coords.x / World.cellSize;
	int gridY = coords.z / World.cellSize;
	int gridZ = coords.y / World.cellSize;

	gridX = std::clamp(gridX, 0, (int)World.dimensions.x - 1);
	gridY = std::clamp(gridY, 0, (int)World.dimensions.y - 1);
	gridZ = std::clamp(gridZ, 0, (int)World.dimensions.z - 1);
	int index = gridIndex({gridX, gridY, gridZ});

	Cell* c = &World.grid[index];
	return c;
}

void placeBuildingAtWorldCoords(Building& building, glm::vec3 worldCoords, bool force) {
	Cell* cell = cellAtWorldCoords(worldCoords);
	if (!cell->occupied || force) {
		cell->occupant = building;
		cell->occupied = true;
	}
}

void placeBuildingAtGridCoords(Building& building, glm::vec3 gridCoords, bool force) {
	Cell* cell = &World.grid[gridIndex(gridCoords)];
	if (!cell->occupied || force) {
		cell->occupant = building;
		cell->occupant.model.translation = cell->worldPosition + glm::vec3(World.cellSize * 0.5f, 0, World.cellSize * 0.5f);
		cell->occupied = true;
	}
}

void removeBuildingAtGridCoords(glm::vec3 gridCoords) {
	Cell* cell = &World.grid[gridIndex(gridCoords)];
	cell->occupant = {};
	cell->occupied = false;
}

void removeBuildingAtWorldCoords(glm::vec3 worldCoords) {
	Cell* cell = cellAtWorldCoords(worldCoords);
	cell->occupant = {};
	cell->occupied = false;
}

int gridIndex(glm::vec3 gridCoords) {
	return gridCoords.x + gridCoords.y * World.dimensions.y + gridCoords.z * World.dimensions.y * World.dimensions.z;
}