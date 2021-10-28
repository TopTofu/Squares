#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <Util/Common.h>

struct Camera {
	glm::vec3 position;
	glm::vec3 orientation;
	glm::vec3 up;

	int width;
	int height;

	bool firstClick = true;

	float speed = CAMERA_SPEED;
	float sensitivity = CAMERA_SENSITIVITY;
};

Camera initCamera(glm::vec3 position, int width, int height);

glm::mat4 getViewMatrix(Camera& camera);
glm::mat4 getProjectionMatrix(int width, int height);
glm::mat4 getCameraMatrix(Camera& camera);
glm::mat4 getOrthogonalMatrix();

void cameraRotateX(Camera& camera, float degrees, bool limit = true);
void cameraRotateY(Camera& camera, float degrees);