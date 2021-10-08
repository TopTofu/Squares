#include <Game/World.h>

World initWorld(int gridSize, float cellSize) {
	World world;
	for (int y = 0; y < gridSize; y++) {
		for (int x = 0; x < gridSize; x++) {
			Cell c;
			c.gridPosition = { x, y };
			c.worldPosition = { x * cellSize, y * cellSize, 0 };

			world.grid.push_back(c);
		}
	}

	world.size = gridSize;
	world.cellSize = cellSize;

	return world;
}


Cell& cellAtWorldCoords(World& world, glm::vec3 coords) {
	double gridX = coords.x / world.cellSize;
	double gridY = coords.y / world.cellSize;

	Cell& c = world.grid[gridY + world.size * gridX];
	return c;
}