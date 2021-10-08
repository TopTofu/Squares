#include <iostream>

#include <Engine/Window.h>
#include <Engine/Render.h>
#include <Engine/Shader.h>
#include <Util/Common.h>
#include <Engine/Controls.h>
#include <Game/World.h>

int main() {

	GLFWwindow* window = initWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
	initOpenGL(window, WINDOW_WIDTH, WINDOW_HEIGHT);

	GLuint vertShader = compileShader("E:/Squares/Resources/Shader/default.vert");
	GLuint fragShader = compileShader("E:/Squares/Resources/Shader/default.frag");
	GLuint shader = createProgram(vertShader, fragShader);

	Camera camera = initCamera(glm::vec3(0.0f, 0.5f, 0.5f), WINDOW_WIDTH, WINDOW_HEIGHT);

	Mesh plane = getQuadMesh({ 0, 0, 0 }, { 20, 0, 0 }, { 0, 0, 20 }, glm::vec4(0.0f, 0.40f, 0.27f, 1.0f));
	plane.shader = shader;

	Mesh quad = getQuadMesh({ 0, 0.1, 0 }, { 0.5, 0, 0 }, { 0, 0, 0.5 }, glm::vec4(0.5f, 0.5f, 1.0f, 1.0f));
	quad.shader = shader;
	
	World w = initWorld(10, 0.5f);

	float delta = 0.0f;
	double currentTime = glfwGetTime();
	double previousTime;
	long frameCount = 0;
	long prevFrameCount = 0;
	float timeAccumulator = 0.0f;

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0 / 255.0f, 30 / 255.0f, 50 / 255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		frameCount++;

		previousTime = currentTime;
		currentTime = glfwGetTime();
		delta = currentTime - previousTime;

		timeAccumulator += delta;
		if (timeAccumulator >= 1.0f) {
			glfwSetWindowTitle(window, (std::to_string(frameCount - prevFrameCount) + " FPS").c_str());
			prevFrameCount = frameCount;
			timeAccumulator = 0.0f;
		}

		handleCameraMovement(window, camera, delta);

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			glm::vec3 inter = getMousePickIntersection(window, camera);
			if (inter != glm::vec3(0.0f, 0.0f, 0.0f)) {
				Cell* c = cellAtWorldCoords(w, inter);
				if (c) {
					quad.translation = c->worldPosition;
					//printf("InterX: %f InterZ: %f | cellX: %f cellZ: %f | quadX: %f quadZ: %f\n", inter.x, inter.z, c->worldPosition.x, c->worldPosition.z, quad.translation.x, quad.translation.z);
				}


			}
		}

		renderMesh(plane, camera);
		renderMesh(quad, camera);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}