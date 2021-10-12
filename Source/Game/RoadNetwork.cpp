#include <Game/RoadNetwork.h>
#include <Game/World.h>

RoadNetworkInfo RoadNetwork;

void initRoadNetwork() {
	if (!World.initialized)
		throw(errno);

	for (int y = 0; y < World.grid.size(); y++) {
		RoadNetwork.roads.push_back(0);
	}
}

void addRoad(glm::vec2 gridPosition) {
	size_t index = World.size * gridPosition.x + gridPosition.y;
	size_t maxIndex = World.size * World.size;
	
	bool north = 0;
	bool east = 0;
	bool south = 0;
	bool west = 0;


	// bugs: check if at grid edge; if so dont look for neighbors in edge direction

	if ((index <= maxIndex - 1) && (gridPosition.y < World.size)) {
		// check and update northern cell
		north = (int)RoadNetwork.roads[index + 1] > 0;
		RoadNetwork.roads[index + 1] |= 1 << 3;
	}
	
	if (index <= maxIndex - World.size && (gridPosition.x < World.size)) {
		// check and update eastern cell
		east = (int)RoadNetwork.roads[index + World.size] > 0;
		RoadNetwork.roads[index + World.size] |= 1 << 4;
	}
	
	if (index >= 1 && (gridPosition.y - 1 >= 0)) {
		// check and update southern cell
		south = (int)RoadNetwork.roads[index - 1] > 0;
		RoadNetwork.roads[index - 1] |= 1 << 1;
	}
	
	if (index >= World.size && (gridPosition.x - 1 >= 0)) {
		// check and update western cell
		west = (int)RoadNetwork.roads[index - World.size] > 0;
		RoadNetwork.roads[index - World.size ] |= 1 << 2;
	}
	
	RoadNetwork.roads[index] = 1 + (north << 1) + (east << 2) + (south << 3) + (west << 4);
}