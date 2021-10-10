#pragma once

#include <GLFW/glfw3.h>
#include <string>

struct Context {
	float dt;
	float fps;

	float currentTime;
	float prevTime;

	long frameCount = 0;
	long prevFrameCount = 0;
	float timeAccumulator = 0.0f;
};

extern Context context;


void updateContext(GLFWwindow* window);
