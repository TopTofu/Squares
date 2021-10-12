#include <iostream>

#include <Engine/Window.h>
#include <Engine/Render.h>
#include <Engine/Shader.h>
#include <Engine/Light.h>
#include <Engine/Controls.h>
#include <Util/Common.h>
#include <Game/World.h>
#include <Game/Interface.h>
#include <Engine/ModelLoader.h>
#include <Util/DebugInterface.h>


int main() {

	GLFWwindow* window = initWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
	initOpenGL(window, WINDOW_WIDTH, WINDOW_HEIGHT);

	GLuint vertShader = compileShader("./Resources/Shader/default.vert");
	GLuint fragShader = compileShader("./Resources/Shader/default.frag");
	GLuint shader = createProgram(vertShader, fragShader);

	GLuint matVert = compileShader("./Resources/Shader/material.vert");
	GLuint matFrag = compileShader("./Resources/Shader/material.frag");
	GLuint matShader = createProgram(matVert, matFrag);

	Camera camera = initCamera(glm::vec3(-1.0f, 4.0f, -1.0f), WINDOW_WIDTH, WINDOW_HEIGHT);
	cameraRotateY(camera, 135);
	cameraRotateX(camera, 40);

	initWorld(20, 1.0f, shader);
	initInterface(window, shader);

	initModelLoader(matShader, glm::vec3(world.cellSize / 2.0f));

	Light light = initLight({ 2.0f, 4.0f, 2.0f });

	initDebugInterface(window);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0 / 255.0f, 30 / 255.0f, 50 / 255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		updateDebugInterface(light);
		updateContext(window);

		applyLightToShader(light, matShader);
		showLight(light, camera, shader);

		handleCameraMovement(window, camera);
		updateInterface(window, camera);

		renderWorld(camera);
		renderInterface(camera);

		renderDebugInterface();
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}