#pragma once

#include <Game/World.h>
#include <Game/RoadNetwork.h>

#include <Engine/Render.h>
#include <Engine/ModelLoader.h>
#include <Engine/Shader.h>
#include <Engine/Camera.h>
#include <Engine/Texture.h>

#include <Util/Utilities.h>


struct CellPicker {
	Model stuckObject;
	Mesh baseMesh;

	bool stuck = false;
};


struct InterfaceElement {
	Mesh mesh;
	void (*callback)(InterfaceElement*);
	bool clickable;

	glm::vec3 p0;
	glm::vec3 p1;
	glm::vec3 p2;
	glm::vec3 p3;

	std::string id;
};


struct InterfaceInfo {
	CellPicker cellPicker;

	std::vector <InterfaceElement> elements;

	bool hovering = false;
	InterfaceElement* hoveredElement;

	bool initialized = false;
};

extern InterfaceInfo Interface;


void initInterface(GLFWwindow* window, GLuint shader);
void initElements();

void sampleCallback(InterfaceElement* element);

void interfaceKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void interfaceMouseCallback(GLFWwindow* window, int button, int action, int mods);

void renderInterface(Camera& camera);
void renderInterfaceElement(Mesh& mesh, Camera& camera);

void updateInterface(GLFWwindow* window, Camera& camera);

void updateCellPicker(GLFWwindow* window, Camera& camera);
void pickCell(glm::vec3 worldCoords);

void stickModelToPicker(Model& model);
void unstuckModelFromPicker();

void rotatePicker(float degrees);

InterfaceElement* getInterfaceElementAtScreenSpace(double x, double y, bool* found);