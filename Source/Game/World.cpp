#include <Game/World.h>

WorldInfo World;

void initWorld(int gridSize, float cellSize, GLuint shader) {
	if (World.initialized) {
		printf("World Struct has already been initialized!");
		return;
	}

	for (int y = 0; y < gridSize; y++) {
		for (int x = 0; x < gridSize; x++) {
			Cell c;
			c.gridPosition = { x, y };
			c.worldPosition = { x * cellSize, 0, y * cellSize };

			World.grid.push_back(c);
		}
	}

	World.size = gridSize;
	World.cellSize = cellSize;

	World.mesh = getQuadMesh({ 0, 0, 0 }, { cellSize * gridSize, 0, 0 }, { 0, 0, cellSize * gridSize }, { 0.09f, 0.34f, 0.23f, 1.0f });
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
	int gridX = coords.x / World.cellSize;
	int gridY = coords.z / World.cellSize;

	gridX = std::clamp(gridX, 0, World.size - 1);
	gridY = std::clamp(gridY, 0, World.size - 1);
	int index = gridX + gridY * World.size;

	Cell* c = &World.grid[index];
	return c;
}


void placeBuilding(Building& building, glm::vec3 worldCoords, bool force) {
	Cell* cell = cellAtWorldCoords(worldCoords);
	if (!cell->occupied || force) {
		cell->occupant = building;
		cell->occupied = true;
	}
}

void placeBuilding(Building& building, glm::vec2 gridCoords, bool force) {
	Cell* cell = &World.grid[gridCoords.x + World.size * gridCoords.y];
	if (!cell->occupied || force) {
		cell->occupant = building;
		cell->occupant.model.translation = cell->worldPosition + glm::vec3(World.cellSize * 0.5f, 0, World.cellSize * 0.5f);
		cell->occupied = true;
	}

}


void removeBuilding(glm::vec2 gridCoords) {
	Cell* cell = &World.grid[gridCoords.x + World.size * gridCoords.y];
	cell->occupant = {};
	cell->occupied = false;
}


void removeBuilding(glm::vec3 worldCoords) {
	Cell* cell = cellAtWorldCoords(worldCoords);
	cell->occupant = {};
	cell->occupied = false;
}

