#pragma once

#include <map>
#include <string>

#include <Engine/Mesh.h>

struct ModelLoader {
	std::map<std::string, Model> models;
};


extern ModelLoader modelLoader;


void initModelLoader(GLuint shader, glm::vec3 scaling = { 1,1,1 });

Model getModelFromLoader(std::string name);

