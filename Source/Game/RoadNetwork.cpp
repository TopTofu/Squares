#include <Game/RoadNetwork.h>

RoadNetworkInfo RoadNetwork;

void initRoadNetwork() {
	if (!World->initialized)
		throw(errno);

	for (int y = 0; y < World->grid.size(); y++) {
		RoadNetwork.roads.push_back(0);
	}
}

void addRoad(glm::vec3 gridPosition) {
	size_t index = gridIndex(gridPosition);

	bool north = 0;
	bool east = 0;
	bool south = 0;
	bool west = 0;

	if (gridPosition.x < World->dimensions.x - 1) {
		north = (int)RoadNetwork.roads[index + 1] & 1;
		RoadNetwork.roads[index + 1] |= 1 << 3; // northern cell now knows that its southern is placed
	}

	if (gridPosition.y < World->dimensions.y - 1) {
		east = (int)RoadNetwork.roads[index + World->dimensions.y] & 1;
		RoadNetwork.roads[index + World->dimensions.y] |= 1 << 4;
	}

	if (gridPosition.x > 0) {
		south = (int)RoadNetwork.roads[index - 1] & 1;
		RoadNetwork.roads[index - 1] |= 1 << 1;
	}

	if (gridPosition.y > 0) {
		west = (int)RoadNetwork.roads[index - World->dimensions.y] & 1;
		RoadNetwork.roads[index - World->dimensions.y] |= 1 << 2;
	}

	RoadNetwork.roads[index] = 1 + (north << 1) + (east << 2) + (south << 3) + (west << 4);
	updateRoadMeshInCell(gridPosition);

	updateRoadMeshInCell({ gridPosition.x,     gridPosition.y + 1, 0 }); // north
	updateRoadMeshInCell({ gridPosition.x + 1, gridPosition.y,     0 }); // east
	updateRoadMeshInCell({ gridPosition.x,	   gridPosition.y - 1, 0 }); // south
	updateRoadMeshInCell({ gridPosition.x - 1, gridPosition.y,     0 }); // west
}



void updateRoadMeshInCell(glm::vec3 gridPosition) {
	int index = gridIndex(gridPosition);
	// @Temporary this maybe need to work in 3D
	if (index >= World->dimensions.x * World->dimensions.y || index < 0) {
		printf("Exceeded World->grid index\n");
		return;
	}

	int road = RoadNetwork.roads[index];

	Model model;
	int connections = 0;

	{
		if (!(road & 1)) {
			//removeBuilding(gridPosition);
			return;
		}

		if (!(road & 2) && !(road & 4) && !(road & 8) && !(road & 16)) {
			model = getRoadEnd();
		}

		else if ((road & 2) && !(road & 4) && !(road & 8) && !(road & 16)) {
			model = getRoadEnd();
			rotateModelBy(model, { 0,1,0 }, -90);
		}

		else if (!(road & 2) && (road & 4) && !(road & 8) && !(road & 16)) {
			model = getRoadEnd();
			rotateModelBy(model, { 0,1,0 }, 180);
		}

		else if ((road & 2) && (road & 4) && !(road & 8) && !(road & 16)) {
			model = getCurvedStreet();
			rotateModelBy(model, { 0,1,0 }, 180);
		}

		else if (!(road & 2) && !(road & 4) && (road & 8) && !(road & 16)) {
			model = getRoadEnd();
			rotateModelBy(model, { 0,1,0 }, 90);
		}

		else if ((road & 2) && !(road & 4) && (road & 8) && !(road & 16)) {
			model = getStraightStreet();
			rotateModelBy(model, { 0,1,0 }, 90);
		}

		else if (!(road & 2) && (road & 4) && (road & 8) && !(road & 16)) {
			model = getCurvedStreet();
			rotateModelBy(model, { 0,1,0 }, 90);
		}

		else if ((road & 2) && (road & 4) && (road & 8) && !(road & 16)) {
			model = getTJunction();
			rotateModelBy(model, { 0,1,0 }, -90);
		}

		else if (!(road & 2) && !(road & 4) && !(road & 8) && (road & 16)) {
			model = getRoadEnd();
		}

		else if ((road & 2) && !(road & 4) && !(road & 8) && (road & 16)) {
			model = getCurvedStreet();
			rotateModelBy(model, { 0,1,0 }, -90);
		}

		else if (!(road & 2) && (road & 4) && !(road & 8) && (road & 16)) {
			model = getStraightStreet();
		}

		else if ((road & 2) && (road & 4) && !(road & 8) && (road & 16)) {
			model = getTJunction();
		}

		else if (!(road & 2) && !(road & 4) && (road & 8) && (road & 16)) {
			model = getCurvedStreet();
		}

		else if ((road & 2) && !(road & 4) && (road & 8) && (road & 16)) {
			model = getTJunction();
			rotateModelBy(model, { 0,1,0 }, 90);
		}

		else if (!(road & 2) && (road & 4) && (road & 8) && (road & 16)) {
			model = getTJunction();
			rotateModelBy(model, { 0,1,0 }, 180);
		}

		else if ((road & 2) && (road & 4) && (road & 8) && (road & 16)) {
			model = getXJunction();
		}
	}

	Building b;
	b.model = model;
	placeBuildingAtGridCoords(b, gridPosition, true);
}


void printNetwork() {
	for (int i = 0; i < World->dimensions.x; i++) {
		int digits = std::to_string(i).size();
		if (digits > 1)
			printf("%i ", i);
		else
			printf("%i  ", i);
	}

	printf("\n");

	printf("-----------------------------------------------------------\n");

	for (int i = 0; i < World->dimensions.x * World->dimensions.y; i++) {
		if (i % (int)World->dimensions.x == 0) printf("\n");
		int digits = std::to_string(RoadNetwork.roads[i]).size();
		if (digits > 1)
			printf("%i ", RoadNetwork.roads[i]);
		else
			printf("%i  ", RoadNetwork.roads[i]);

	}

	printf("\n");
}