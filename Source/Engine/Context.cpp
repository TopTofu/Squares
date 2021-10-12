#include <Engine/Context.h>

ContextInfo Context;

void updateContext(GLFWwindow* window) {
	Context.frameCount++;

	Context.prevTime = Context.currentTime;
	Context.currentTime = glfwGetTime();
	Context.dt = Context.currentTime - Context.prevTime;

	Context.timeAccumulator += Context.dt;
	if (Context.timeAccumulator >= 1.0f) {
		Context.fps = Context.frameCount - Context.prevFrameCount;
		Context.prevFrameCount = Context.frameCount;
		Context.timeAccumulator = 0.0f;
	}
}