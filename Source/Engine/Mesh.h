#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <string>
#include <fstream>

#include <Engine/Camera.h>
#include <Util/Utilities.h>

struct Vertex {
	glm::vec3 position;
	glm::vec2 uv = glm::vec2(0.0f, 0.0f);
	glm::vec4 color;
	glm::vec3 normal;
};


enum IlluminationMode {
	ColorOnAmbientOff = 0,
	ColorOnAmbientOn = 1,
	HighlightOn = 2,
	RelfectionOnRayTraceOn = 3,
	GlassOnRayTraceOn = 4,
	FresnelOnRayTraceOn = 5,
	RefractionOnFesnelOffRayTraceOn = 6,
	RefractionOnFresnelOnRayTraceOn = 7,
	ReflectionOnRayTraceOff = 8,
	GlassOnRayTraceOff = 9,
	ShadowsOnInvisibleSurfaces = 10
};


struct Material {
	std::string name;
	std::string file;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float opaqueness;
	float refractionIndex;

	float specularExponent;

	IlluminationMode illuminationMode;
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


Mesh getQuadMesh(glm::vec3 origin, glm::vec3 s0, glm::vec3 s1, glm::vec4 color = { 1, 1, 1, 1 }, bool buffer = true);
Mesh getCircleMesh(float r, int numSegements, glm::vec4 color = { 1, 1, 1, 1 });

void bufferMesh(Mesh& mesh);

void translateMeshTo(Mesh& mesh, glm::vec3 destination);
void translateMeshBy(Mesh& mesh, glm::vec3 offset);

void scaleMeshTo(Mesh& mesh, glm::vec3 scale);
void scaleMeshBy(Mesh& mesh, glm::vec3 scale);

void rotateMeshBy(Mesh& mesh, glm::vec3 axis, float degrees);

Mesh loadOBJ(std::string filePath, bool buffer = true);
std::vector<Material> loadMtl(std::string filePath);