#include <iostream>

#include <glad/glad.h>

#include "Engine/Window.h"
#include "Engine/Render.h"
#include "Engine/Shader.h"
#include "Engine/Light.h"
#include "Engine/Controls.h"
#include "Engine/ModelLoader.h"
#include "Engine/Font.h"

#include "Util/Common.h"
#include "Util/DebugInterface.h"

#include "Game/World.h"
#include "Game/Interface.h"
#include "Game/RoadNetwork.h"

int main() {
	GLFWwindow* window = initWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
	initOpenGL(window, WINDOW_WIDTH, WINDOW_HEIGHT);

	loadShaders();
	loadTextures("./Resources/Textures/");

	FontInfo font = loadFont("C:/Windows/Fonts/arial.ttf");
	BitmapInfo bitmap = getCodePoint(font, 'A');
	createTextureFromBitmap(&bitmap, true, "testFont");

	Camera camera = initCamera(glm::vec3(-1.0f, 4.0f, -1.0f), WINDOW_WIDTH, WINDOW_HEIGHT);
	cameraRotateY(camera, 135);
	cameraRotateX(camera, 40);

	initWorld({ 20, 20, 5 }, 1.0f, getShader("default").handle);
	initInterface(window, getShader("default").handle);

	initRoadNetwork();

	initModelLoader(getShader("material").handle, glm::vec3(World->cellSize / 2.0f));

	Light light = initLight({ 10.0f, 20.0f, 10.0f });

	initDebugInterface(window);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0 / 255.0f, 30 / 255.0f, 50 / 255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		updateDebugInterface(light);
		updateContext(window);

		applyLightToShader(light, getShader("material").handle);
		showLight(light, camera, getShader("default").handle);

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