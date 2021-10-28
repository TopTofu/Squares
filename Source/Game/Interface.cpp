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

	// @Temporary
	InterfaceElement button;
	button.clickable = true;
	button.callback = sampleCallback;

	button.p0 = { 50, 50,  0 };
	button.p1 = { 150,  50,  0 };
	button.p2 = { 150,  150,  0 };
	button.p3 = { 50,  150,  0 };

	button.mesh = getQuadMesh(button.p0, button.p1 - button.p0, button.p3 - button.p0, { 1.0, 0.5, 0.5, 0.8 });
	button.mesh.shader = shader;

	translateMeshBy(button.mesh, { 0, 500, 0 });

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
		if (Interface.hovering && Interface.hoveredElement->clickable) {
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
		updateCellPicker(window, camera);
	}
}


void updateCellPicker(GLFWwindow* window, Camera& camera) {
	bool hit;

	glm::vec3 intersection = getMousePickIntersection(window, camera, hit);
	if (hit) {
		pickCell(intersection);
	}
}


InterfaceElement* getInterfaceElementAtScreenSpace(double x, double y, bool* found) {
	glm::vec4 pixel = { getPixelCoords(x, y), 0, 1 };

	for (InterfaceElement& element : Interface.elements) {
		// @Temporary this only works on quads
		// @Temporary does not yet support scale and rotation of elements

		// apply the inverse translation of the element to the cursor coords
		glm::mat4 transl = glm::mat4(1.0f);
		transl = glm::translate(transl, -element.mesh.translation);
		glm::vec4 temp = transl * pixel;
		if (element.p0.x <= temp.x && element.p1.x >= temp.x && element.p0.y <= temp.y && element.p3.y >= temp.y) {
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
		renderInterfaceElement(element.mesh, camera);
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


void renderInterfaceElement(Mesh& mesh, Camera& camera) {
	glDisable(GL_DEPTH_TEST);

	glUseProgram(mesh.shader);

	glBindVertexArray(mesh.vao);

	glm::mat4 ortho = getOrthogonalMatrix();
	glUniformMatrix4fv(glGetUniformLocation(mesh.shader, "ortho"), 1, GL_FALSE, glm::value_ptr(ortho));

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

	glEnable(GL_DEPTH_TEST);
}