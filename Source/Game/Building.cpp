#include <Game/Building.h>


void renderBuilding(Building& building, Camera& camera) {
	renderModel(building.model, camera);
}


