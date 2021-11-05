#pragma once

#include <glm/glm.hpp>

#include "Util/Common.h"

#include <vector>
#include <string>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

glm::vec2 getNormalizedDeviceCoords(float mouseX, float mouseY);
glm::vec2 getPixelCoords(float x, float y);
std::vector<std::string> splitAt(std::string s, const char* c);
std::string getFileNameFromPath(std::string path);