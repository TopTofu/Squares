#pragma once

#include <iostream>

#include <Engine/Camera.h>
#include <Engine/Camera.h>
#include <Game/Interface.h>

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <GLFW/glfw3.h>



void handleCameraMovement(GLFWwindow* window, Camera& camera, float delta);
void handleInterfaceInput(GLFWwindow* window, Camera& camera);
