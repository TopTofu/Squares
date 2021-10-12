#include <Engine/ModelLoader.h>

ModelLoader modelLoader;

std::string modelPaths[] = {
	"./Resources/Models/house02.obj",
	"./Resources/Models/house03.obj",
	"./Resources/Models/house04.obj",
};


void initModelLoader(GLuint shader, glm::vec3 scaling) {
	for (std::string path : modelPaths) {
		Model m = loadOBJ(path);
		m.scale = scaling;

		for (Mesh& mesh : m.meshes)
			mesh.shader = shader;

		modelLoader.models.emplace(m.name, m);
	}
}


Model getModelFromLoader(std::string name) {
	return modelLoader.models[name];
}