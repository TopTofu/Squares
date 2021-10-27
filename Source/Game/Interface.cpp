#include <Game/Interface.h>
#include <Game\RoadNetwork.h>
#include <Engine\Shader.h>

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
	Interface.cellPicker.baseMesh = getQuadMesh({ 0, 0.001f, 0 }, { cellSize, 0, 0 }, { 0, 0, cellSize }, { 0.2f, 0.45f, 0.35f, 1.0f });
	Interface.cellPicker.baseMesh.shader = shader;

	Interface.initialized = true;

	glfwSetKeyCallback(window, interfaceKeyCallback);
	glfwSetMouseButtonCallback(window, interfaceMouseCallback);

	initElements();
}


void sampleCallback() {
	printf("Hey, this worked!!\n");
}


void initElements() {
	GLuint shader = getShader("interface").handle;

	// sample button
	InterfaceElement button;
	button.clickable = true;
	button.callback = sampleCallback;

	button.p0 = { 0,0,0 };
	button.p1 = { 0.5,0,0 };
	button.p2 = { 0.5,0.5,0 };
	button.p3 = { 0,0.5,0 };

	button.mesh = getQuadMesh(button.p0, button.p1, button.p3, { 1.0, 0.5, 0.5, 0.5 });
	button.mesh.shader = shader;



	Interface.elements.push_back(button);
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
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		unstuckModelFromPicker();
	}
	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		rotatePicker(90.0f);
	}
}

void interfaceMouseCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		if (Interface.hovering) {
			(Interface.hoveredElement->callback)();
		}
		else {
			// @Temporary
			Cell* cell = cellAtWorldCoords(Interface.cellPicker.baseMesh.translation);
			if (!cell->occupied)
			{
				addRoad(cell->gridPosition);
			}
			/*if (Interface.cellPicker.stuck) {
			Building b;
			b.model = Interface.cellPicker.stuckObject;
			placeBuilding(b, Interface.cellPicker.baseMesh.translation);
			}*/
		}
	}
}

void updateInterface(GLFWwindow* window, Camera& camera) {
	updateCellPicker(window, camera);
}


void updateCellPicker(GLFWwindow* window, Camera& camera) {
	bool hit;

	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	glm::vec2 deviceCoords = getNormalizedDeviceCoords(mouseX, mouseY);

	bool found = false;
	InterfaceElement* element = getInterfaceElementAtScreenSpace(deviceCoords.x, deviceCoords.y, &found);
	if (found) {
		Interface.hovering = true;

		Interface.hoveredElement = element;
	}
	else {
		Interface.hovering = false;

		glm::vec3 intersection = getMousePickIntersection(window, camera, hit);
		if (hit) {
			pickCell(intersection);
		}
	}
}


InterfaceElement* getInterfaceElementAtScreenSpace(double x, double y, bool* found) {
	for (InterfaceElement& element : Interface.elements) {
		if (x > element.p0.x && x < element.p2.x && y > element.p0.y && y < element.p2.y) {
			*found = true;
			return &element;
		}
	}

	*found = false;
	return {};
}


void renderInterface(Camera& camera) {
	renderMesh(Interface.cellPicker.baseMesh, camera);
	if (Interface.cellPicker.stuck)
		renderModel(Interface.cellPicker.stuckObject, camera);

	for (InterfaceElement& element : Interface.elements) {
		renderInterfaceElement(element.mesh);
	}
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


void renderInterfaceElement(Mesh mesh) {
	glUseProgram(mesh.shader);

	glBindVertexArray(mesh.vao);

	glm::mat4 transl = glm::mat4(1.0f);
	glm::mat4 rot = glm::mat4(1.0f);
	glm::mat4 sca = glm::mat4(1.0f);

	transl = glm::translate(transl, mesh.translation);
	rot = glm::mat4_cast(mesh.rotation);
	sca = glm::scale(sca, mesh.scale);

	glm::mat4 transform = transl * rot * sca;
	glUniformMatrix4fv(glGetUniformLocation(mesh.shader, "transform"), 1, GL_FALSE, glm::value_ptr(transform));

	glDrawElements(mesh.primitive, mesh.indices.size(), GL_UNSIGNED_INT, 0);

	glUseProgram(0);
	glBindVertexArray(0);
}