#include <Engine/Controls.h>

glm::vec3 getMousePickIntersection(GLFWwindow* window, Camera& camera) {
	double mouseX, mouseY;

	glfwGetCursorPos(window, &mouseX, &mouseY);

	glm::vec2 normalized = getNormalizedDeviceCoords(mouseX, mouseY);

	glm::vec4 clip = glm::vec4(normalized, -1.0f, 1.0f);

	glm::mat4 invProj = glm::inverse(getProjectionMatrix(WINDOW_WIDTH, WINDOW_HEIGHT));

	glm::vec4 temp = invProj * clip;
	glm::vec4 eyeCoords = glm::vec4(temp.x, temp.y, -1.0f, 0.0f);

	glm::mat4 invView = glm::inverse(getViewMatrix(camera));
	temp = invView * eyeCoords;
	glm::vec3 ray = glm::normalize(glm::vec3(temp.x, temp.y, temp.z));

	std::cout << "";

	glm::vec3 origin = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 planeNormal = glm::vec3(0.0f, 1.0f, 0.0f);
	float distance;

	if (!glm::intersectRayPlane(camera.position, ray, origin, planeNormal, distance)) {
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}

	return camera.position + distance * ray;
}


glm::vec2 getNormalizedDeviceCoords(float mouseX, float mouseY) {
	float x = mouseX / WINDOW_WIDTH * 2.0f - 1.0f;
	float y = mouseY / WINDOW_HEIGHT * -2.0f + 1.0f;

	return glm::vec2(x, y);
}


void handleCameraMovement(GLFWwindow* window, Camera& camera, float delta) {
	const float speed = camera.speed * delta;
	const float sensitivity = camera.sensitivity;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.position += speed * camera.orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.position -= speed * camera.orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.position -= glm::normalize(glm::cross(camera.orientation, camera.up)) * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.position += glm::normalize(glm::cross(camera.orientation, camera.up)) * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		camera.position += speed * camera.up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		camera.position += speed * -camera.up;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		if (camera.firstClick) {
			glfwSetCursorPos(window, (camera.width / 2), (camera.height / 2));
			camera.firstClick = false;
		}

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		double mouseX;
		double mouseY;

		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotX = sensitivity * (float)(mouseY - (camera.height / 2)) / camera.height;
		float rotY = sensitivity * (float)(mouseX - (camera.width / 2)) / camera.width;

		cameraRotateX(camera, rotX);
		cameraRotateY(camera, rotY);
		
		glfwSetCursorPos(window, (camera.width / 2), (camera.height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		camera.firstClick = true;
	}
}