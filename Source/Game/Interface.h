#pragma once

#include <Game/World.h>
#include <Engine/Render.h>
#include <Util/Utilities.h>


struct CellPicker {
	Model stuckObject;
	Mesh baseMesh;

	bool stuck = false;
};

struct Interface {
	CellPicker cellPicker;

	bool initialized = false;
};

extern Interface interface;


void initInterface(GLFWwindow* window, GLuint shader);

void interfaceKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

void renderInterface(Camera& camera);

void updateInterface(GLFWwindow* window, Camera& camera);

void updateCellPicker(GLFWwindow* window, Camera& camera);
void pickCell(glm::vec3 worldCoords);

void stickModelToPicker(Model& model);
void unstuckModelFromPicker();

void rotatePicker(float degrees);
