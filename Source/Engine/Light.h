#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Engine/Mesh.h"
#include "Engine/Render.h"


struct Light {
	glm::vec3 position;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	Mesh mesh;
	bool visible = true;
};


Light initLight(glm::vec3 position = { 0,0,0 },
	glm::vec3 ambient = { 0.1f, 0.1f, 0.1f },
	glm::vec3 diffuse = { 0.5f, 0.5f, 0.5f },
	glm::vec3 specular = { 1.0f, 1.0f, 1.0f });

void applyLightToShader(Light& light, GLuint shader);
void showLight(Light& light, Camera& camera, GLuint shader);