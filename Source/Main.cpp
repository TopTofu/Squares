#include <iostream>

#include <Engine/Window.h>
#include <Engine/Render.h>
#include <Engine/Shader.h>
#include <Util/Common.h>
#include <Engine/Controls.h>

int main() {

	GLFWwindow* window = initWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
	initOpenGL(window, WINDOW_WIDTH, WINDOW_HEIGHT);

	GLuint vertShader = compileShader("E:/Squares/Resources/Shader/default.vert");
	GLuint fragShader = compileShader("E:/Squares/Resources/Shader/default.frag");
	GLuint shader = createProgram(vertShader, fragShader);
	
	Camera camera = initCamera(glm::vec3(0.0f, 0.5f, 0.5f), WINDOW_WIDTH, WINDOW_HEIGHT);

	Mesh plane = getQuadMesh(0.0f, 0.0f, 0.0f, 20.0f, 20.0f, glm::vec4(0.0f, 0.40f, 0.27f, 1.0f));
	plane.shader = shader;
	rotateMeshBy(plane, glm::vec3(1.0f, 0.0f, 0.0f), 90.0f);

	Mesh quad = getQuadMesh(0.0f, 0.0f, -0.1f, 0.3f, 0.3f, glm::vec4(0.5f, 0.5f, 1.0f, 1.0f));
	quad.shader = shader;
	rotateMeshBy(quad, glm::vec3(1.0f, 0.0f, 0.0f), 90.0f);


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
			if(inter != glm::vec3(0.0f,0.0f,0.0f)){
				quad.translation = inter;
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