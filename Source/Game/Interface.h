#pragma once

#include <Game/World.h>
#include <Engine/Render.h>
#include <Util/Utilities.h>


struct Interface {
	Mesh cellPicker;

	bool initialized = false;
};

extern Interface interface;


void initInterface(GLuint shader);

void renderInterface(Camera& camera);

void updateCellPicker(GLFWwindow* window, Camera& camera);
void pickCell(glm::vec3 worldCoords);
