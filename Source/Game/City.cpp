#include <Game/City.h>


City city;

void placeBuilding(Building& building, Cell& cell) {
	building.gridPosition = cell.gridPosition;

	city.buildings.push_back(building);
}


void renderCity(Camera& camera) {
	for (Building& building : city.buildings) {
		renderBuilding(building, camera);
	}
}