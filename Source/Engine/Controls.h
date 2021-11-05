#pragma once

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Engine/Camera.h"
#include "Engine/Camera.h"
#include "Game/Interface.h"
#include "Engine/Context.h"

#include <GLFW/glfw3.h>

void handleCameraMovement(GLFWwindow* window, Camera& camera);
void handleInterfaceInput(GLFWwindow* window, Camera& camera);
