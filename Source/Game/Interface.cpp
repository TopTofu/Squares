#include <Game/Interface.h>

InterfaceInfo Interface;

void pickCell(glm::vec3 worldCoords) {
	Cell* c = cellAtWorldCoords(worldCoords);
	Interface.cellPicker.baseMesh.translation = c->worldPosition;
	Interface.cellPicker.stuckObject.translation = c->worldPosition + glm::vec3(World.cellSize * 0.5f, 0.0f, World.cellSize * 0.5f);
}


void initInterface(GLFWwindow* window, GLuint shader) {
	if (Interface.initialized) {
		printf("Interface has already been initialized!");
		return;
	}

	if (!World.initialized) {
		printf("World needs to be initilized before Interface!");
		return;
	}

	float cellSize = World.cellSize;
	Interface.cellPicker.baseMesh = getQuadMesh({ 0, 0.001f, 0 }, { cellSize, 0, 0 }, { 0, 0, cellSize }, { 0.5f, 0.5f, 1.0f, 1.0f });
	Interface.cellPicker.baseMesh.shader = shader;

	Interface.initialized = true;

	glfwSetKeyCallback(window, interfaceKeyCallback);
	glfwSetMouseButtonCallback(window, interfaceMouseCallback);
}


void interfaceKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		Model m = getModelFromLoader("house02");
		stickModelToPicker(m);
	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		Model m = getModelFromLoader("house03");
		stickModelToPicker(m);
	}
	if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
		Model m = getModelFromLoader("house04");
		stickModelToPicker(m);
	}
	if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
		Model m = getModelFromLoader("street_straight");
		stickModelToPicker(m);
	}
	if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
		Model m = getModelFromLoader("street_curve");
		stickModelToPicker(m);
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		unstuckModelFromPicker();
	}
	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		rotatePicker(90.0f);
	}
}

void interfaceMouseCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		if (Interface.cellPicker.stuck) {
			Building b;
			b.model = Interface.cellPicker.stuckObject;
			placeBuilding(b, Interface.cellPicker.baseMesh.translation);
		}
	}
}

void updateInterface(GLFWwindow* window, Camera& camera) {
	updateCellPicker(window, camera);
}


void updateCellPicker(GLFWwindow* window, Camera& camera) {
	bool hit;
	glm::vec3 intersection = getMousePickIntersection(window, camera, hit);
	if (hit)
		pickCell(intersection);
}


void renderInterface(Camera& camera) {
	renderMesh(Interface.cellPicker.baseMesh, camera);
	if (Interface.cellPicker.stuck)
		renderModel(Interface.cellPicker.stuckObject, camera);
}


void stickModelToPicker(Model& model) {
	Interface.cellPicker.stuckObject = model;
	Interface.cellPicker.stuck = true;
}


void unstuckModelFromPicker() {
	Interface.cellPicker.stuckObject = {};
	Interface.cellPicker.stuck = false;
}

void rotatePicker(float degrees) {
	Interface.cellPicker.stuckObject.rotation = glm::rotate(Interface.cellPicker.stuckObject.rotation, glm::radians(degrees), { 0, 1, 0 });
}