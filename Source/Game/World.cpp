#include <Game/World.h>
#include <algorithm>

World initWorld(int gridSize, float cellSize) {
	World world;
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

	return world;
}


Cell* cellAtWorldCoords(World& world, glm::vec3 coords) {
	int gridX = coords.x / world.cellSize;
	int gridY = coords.z / world.cellSize;

	gridX = std::clamp(gridX, 0, world.size - 1);
	gridY = std::clamp(gridY, 0, world.size - 1);
	int index = gridY + world.size * gridX;

	Cell* c = &world.grid[index];
	return c;
}