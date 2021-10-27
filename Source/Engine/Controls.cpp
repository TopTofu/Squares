#include <Engine/Controls.h>


void handleCameraMovement(GLFWwindow* window, Camera& camera) {
	const float speed = camera.speed * Context.dt;
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

		// this laggs everything when called
		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); 

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

