#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include <Engine/Camera.h>

#include <vector>
#include <string>

glm::vec2 getNormalizedDeviceCoords(float mouseX, float mouseY);
glm::vec2 getPixelCoords(float x, float y);
glm::vec3 getMousePickIntersection(GLFWwindow* window, Camera& camera, bool& hit);
std::vector<std::string> splitAt(std::string s, const char* c);
