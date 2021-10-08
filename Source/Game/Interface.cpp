#include <Game/Interface.h>


Interface interface;

void pickCell(glm::vec3 worldCoords) {
	Cell* c = cellAtWorldCoords(worldCoords);
	interface.cellPicker.translation = c->worldPosition;
}


void initInterface(GLuint shader) {
	if (interface.initialized) {
		printf("Interface has already been initialized!");
		return;
	}

	if (!world.initialized) {
		printf("World needs to be initilized before Interface!");
		return;
	}

	float cellSize = world.cellSize;
	interface.cellPicker = getQuadMesh({ 0, 0.001f, 0 }, { cellSize, 0, 0 }, { 0, 0, cellSize }, { 0.5f, 0.5f, 1.0f, 1.0f });
	interface.cellPicker.shader = shader;

	interface.initialized = true;
}


void updateCellPicker(GLFWwindow* window, Camera& camera) {
	bool hit;
	glm::vec3 intersection = getMousePickIntersection(window, camera, hit);
	if (hit) pickCell(intersection);
}


void renderInterface(Camera& camera) {
	renderMesh(interface.cellPicker, camera);
}

