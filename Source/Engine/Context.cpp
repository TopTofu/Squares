#include <Engine/Context.h>

Context context;

void updateContext(GLFWwindow* window) {
	context.frameCount++;

	context.prevTime = context.currentTime;
	context.currentTime = glfwGetTime();
	context.dt = context.currentTime - context.prevTime;

	context.timeAccumulator += context.dt;
	if (context.timeAccumulator >= 1.0f) {
		glfwSetWindowTitle(window, (std::to_string(context.frameCount - context.prevFrameCount) + " FPS").c_str());
		context.prevFrameCount = context.frameCount;
		context.timeAccumulator = 0.0f;
	}
}