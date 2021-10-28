#pragma once

#include <glm/glm.hpp>

#include <Util/Common.h>

#include <vector>
#include <string>

glm::vec2 getNormalizedDeviceCoords(float mouseX, float mouseY);
glm::vec2 getPixelCoords(float x, float y);
std::vector<std::string> splitAt(std::string s, const char* c);
std::string getFileNameFromPath(std::string path);