#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include <Engine/Camera.h>

struct Vertex {
	glm::vec3 position;
	glm::vec2 uv = glm::vec2(0.0f, 0.0f);
	glm::vec4 color;
};

struct Mesh {
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	int primitive = GL_TRIANGLES;
	GLuint vao;

	GLuint shader;

	glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
};


Mesh getQuadMesh(float mX, float mY, float mZ, float w, float h, glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f), bool buffer = true);
Mesh getCircleMesh(float r, int numSegements, glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f));

void bufferMesh(Mesh& mesh);

void translateMeshTo(Mesh& mesh, glm::vec3 destination);
void translateMeshBy(Mesh& mesh, glm::vec3 offset);

void scaleMeshTo(Mesh& mesh, glm::vec3 scale);
void scaleMeshBy(Mesh& mesh, glm::vec3 scale);

void rotateMeshBy(Mesh& mesh, glm::vec3 axis, float degrees);

