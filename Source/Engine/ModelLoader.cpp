#include <Engine/ModelLoader.h>

ModelLoaderInfo ModelLoader;

std::string modelPaths[] = {
	"./Resources/Models/house02.obj",
	"./Resources/Models/house03.obj",
	"./Resources/Models/house04.obj",
	"./Resources/Models/street_straight.obj",
	"./Resources/Models/street_curve.obj",
};


void initModelLoader(GLuint shader, glm::vec3 scaling) {
	for (std::string path : modelPaths) {
		Model m = loadOBJ(path);
		m.scale = scaling;

		for (Mesh& mesh : m.meshes)
			mesh.shader = shader;

		ModelLoader.models.emplace(m.name, m);
	}
}


Model getModelFromLoader(std::string name) {
	return ModelLoader.models[name];
}