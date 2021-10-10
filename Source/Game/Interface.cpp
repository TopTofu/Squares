#include <Game/Interface.h>
#include <Engine/ModelLoader.h>

Interface interface;

void pickCell(glm::vec3 worldCoords) {
	Cell* c = cellAtWorldCoords(worldCoords);
	interface.cellPicker.baseMesh.translation = c->worldPosition;
	interface.cellPicker.stuckObject.translation = c->worldPosition;
}


void initInterface(GLFWwindow* window, GLuint shader) {
	if (interface.initialized) {
		printf("Interface has already been initialized!");
		return;
	}

	if (!world.initialized) {
		printf("World needs to be initilized before Interface!");
		return;
	}

	float cellSize = world.cellSize;
	interface.cellPicker.baseMesh = getQuadMesh({ 0, 0.001f, 0 }, { cellSize, 0, 0 }, { 0, 0, cellSize }, { 0.5f, 0.5f, 1.0f, 1.0f });
	interface.cellPicker.baseMesh.shader = shader;

	interface.initialized = true;

	glfwSetKeyCallback(window, interfaceKeyCallback);
}


void interfaceKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		Model m = getModelFromLoader("house");
		stickModelToPicker(m);
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		unstuckModelFromPicker();
	}
}


void updateInterface(GLFWwindow* window, Camera& camera) {
	updateCellPicker(window, camera);
}


void updateCellPicker(GLFWwindow* window, Camera& camera) {
	bool hit;
	glm::vec3 intersection = getMousePickIntersection(window, camera, hit);
	if (hit) pickCell(intersection);
}


void renderInterface(Camera& camera) {
	renderMesh(interface.cellPicker.baseMesh, camera);
	if (interface.cellPicker.stuck) 
		renderModel(interface.cellPicker.stuckObject, camera);
}


void stickModelToPicker(Model& model) {
	interface.cellPicker.stuckObject = model;
	interface.cellPicker.stuck = true;
}


void unstuckModelFromPicker() {
	interface.cellPicker.stuckObject = {};
	interface.cellPicker.stuck = false;
}