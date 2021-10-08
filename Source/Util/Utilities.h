#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include <Engine/Camera.h>

glm::vec2 getNormalizedDeviceCoords(float mouseX, float mouseY);
glm::vec3 getMousePickIntersection(GLFWwindow* window, Camera& camera, bool& hit);