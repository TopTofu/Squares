#pragma once

#include <iostream>

#include <Engine/Camera.h>
#include <Engine/Camera.h>

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <GLFW/glfw3.h>




glm::vec3 getMousePickIntersection(GLFWwindow* window, Camera& camera);
glm::vec2 getNormalizedDeviceCoords(float mouseX, float mouseY);
void handleCameraMovement(GLFWwindow* window, Camera& camera, float delta);

