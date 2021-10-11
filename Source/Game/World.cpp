#include <Game/World.h>

World world;

void initWorld(int gridSize, float cellSize, GLuint shader) {
	if (world.initialized) {
		printf("World Struct has already been initialized!");
		return;
	}

	for (int y = 0; y < gridSize; y++) {
		for (int x = 0; x < gridSize; x++) {
			Cell c;
			c.gridPosition = { x, y };
			c.worldPosition = { y * cellSize, 0, x * cellSize }; // this works but i dont know why

			world.grid.push_back(c);
		}
	}

	world.size = gridSize;
	world.cellSize = cellSize;

	world.mesh = getQuadMesh({ 0, 0, 0 }, { cellSize * gridSize, 0, 0 }, { 0, 0, cellSize * gridSize }, { 0.09f, 0.34f, 0.23f, 1.0f });
	world.mesh.shader = shader;

	world.initialized = true;
}

void renderWorld(Camera& camera) {
	renderMesh(world.mesh, camera);

	for (Cell& cell : world.grid) {
		if (cell.occupied)
			renderBuilding(cell.occupant, camera);
	}
}


Cell* cellAtWorldCoords(glm::vec3 coords) {
	int gridX = coords.x / world.cellSize;
	int gridY = coords.z / world.cellSize;

	gridX = std::clamp(gridX, 0, world.size - 1);
	gridY = std::clamp(gridY, 0, world.size - 1);
	int index = gridY + world.size * gridX;

	Cell* c = &world.grid[index];
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
