#pragma once

#include <GLFW/glfw3.h>
#include <string>

struct ContextInfo {
	float dt;
	float fps;

	float currentTime;
	float prevTime;

	long frameCount = 0;
	long prevFrameCount = 0;
	float timeAccumulator = 0.0f;
};

extern ContextInfo Context;


void updateContext(GLFWwindow* window);
