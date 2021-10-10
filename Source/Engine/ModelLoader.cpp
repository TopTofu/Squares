#include <Engine/ModelLoader.h>

ModelLoader modelLoader;

void initModelLoader(GLuint shader, glm::vec3 scaling) {
	Model m = loadOBJ("E:/Squares/Resources/Models/house.obj");
	m.scale = scaling;
	
	for (Mesh& mesh : m.meshes)
		mesh.shader = shader;

	modelLoader.models.emplace(m.name, m);
}


Model getModelFromLoader(std::string name) {
	return modelLoader.models[name];
}