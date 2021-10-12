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
			c.worldPosition = { y * cellSize, 0, x * cellSize }; // this works but i dont know why

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
	int index = gridY + World.size * gridX;

	Cell* c = &World.grid[index];
	return c;
}


void placeBuilding(Building& building, glm::vec3 coords) {
	Cell* cell = cellAtWorldCoords(coords);
	if (!cell->occupied)
	{
		cell->occupant = building;
		cell->occupied = true;
	}
}
