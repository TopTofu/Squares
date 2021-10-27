#include <Util/Utilities.h>


glm::vec2 getNormalizedDeviceCoords(float mouseX, float mouseY) {
	float x = mouseX / WINDOW_WIDTH * 2.0f - 1.0f;
	float y = mouseY / WINDOW_HEIGHT * -2.0f + 1.0f;

	return glm::vec2(x, y);
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


std::vector<std::string> splitAt(std::string s, const char* c) {
	std::vector<std::string> result = {};

	int size = s.size();

	for (int i = 0; i < size; i++) {
		size_t index = s.find_first_of(c);

		if (index == -1) {
			result.push_back(s);
			break;
		}

		if (index > 0)
			result.push_back(s.substr(0, index));
		s.erase(0, index + 1);
	}

	return result;
}