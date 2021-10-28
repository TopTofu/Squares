#include "Engine/Camera.h"


Camera initCamera(glm::vec3 position, int width, int height) {
	Camera camera = Camera();
	camera.position = position;
	camera.orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	camera.up = glm::vec3(0.0f, 1.0f, 0.0f);

	camera.width = width;
	camera.height = height;

	return camera;
}

glm::mat4 getViewMatrix(Camera& camera) {
	return glm::lookAt(camera.position, camera.position + camera.orientation, camera.up);
}

glm::mat4 getProjectionMatrix(int width, int height) {
	return glm::perspective(glm::radians(CAMERA_FOV), (float)width / (float)height, 0.1f, 100.0f);
}

glm::mat4 getCameraMatrix(Camera& camera) {
	return getProjectionMatrix(WINDOW_WIDTH, WINDOW_HEIGHT) * getViewMatrix(camera);
}

void cameraRotateX(Camera& camera, float degrees, bool limit) {
	glm::vec3 orientation = glm::rotate(camera.orientation, glm::radians(-degrees), glm::normalize(glm::cross(camera.orientation, camera.up)));
	if (!limit) 
		camera.orientation = orientation;

	else if (glm::angle(orientation, camera.up) >= 0.1f && glm::angle(orientation, -camera.up) >= 0.1f) {
		camera.orientation = orientation;
	}
}

void cameraRotateY(Camera& camera, float degrees) {
	camera.orientation = glm::rotate(camera.orientation, glm::radians(-degrees), camera.up);
}

glm::mat4 getOrthogonalMatrix() {
	return glm::ortho<float>(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, -1, 1);
}

glm::vec3 getMousePickIntersection(GLFWwindow* window, Camera& camera, bool& hit) {
	double mouseX, mouseY;
	hit = true;

	glfwGetCursorPos(window, &mouseX, &mouseY);

	glm::vec2 normalized = getNormalizedDeviceCoords(mouseX, mouseY);

	glm::vec4 clip = glm::vec4(normalized, -1.0f, 1.0f);

	glm::mat4 invProj = glm::inverse(getProjectionMatrix(WINDOW_WIDTH, WINDOW_HEIGHT));

	glm::vec4 temp = invProj * clip;
	glm::vec4 eyeCoords = glm::vec4(temp.x, temp.y, -1.0f, 0.0f);

	glm::mat4 invView = glm::inverse(getViewMatrix(camera));
	temp = invView * eyeCoords;
	glm::vec3 ray = glm::normalize(glm::vec3(temp.x, temp.y, temp.z));

	glm::vec3 origin = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 planeNormal = glm::vec3(0.0f, 1.0f, 0.0f);
	float distance;

	if (!glm::intersectRayPlane(camera.position, ray, origin, planeNormal, distance)) {
		hit = false;
	}

	return camera.position + distance * ray;
}