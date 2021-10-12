#include <Engine/Light.h>

Light initLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
	Light light;
	light.position = position;
	light.ambient = ambient;
	light.diffuse = diffuse;
	light.specular = specular;

	light.mesh = getQubeMesh(0.2f);

	return light;
}


void applyLightToShader(Light& light, GLuint shader) {
	glUseProgram(shader);
	glUniform3fv(glGetUniformLocation(shader, "light.position"), 1, glm::value_ptr(light.position));
	glUniform3fv(glGetUniformLocation(shader, "light.ambient"), 1, glm::value_ptr(light.ambient));
	glUniform3fv(glGetUniformLocation(shader, "light.diffuse"), 1, glm::value_ptr(light.diffuse));
	glUniform3fv(glGetUniformLocation(shader, "light.specular"), 1, glm::value_ptr(light.specular));
	glUseProgram(0);
}


void showLight(Light& light, Camera& camera, GLuint shader) {
	light.mesh.shader = shader;
	light.mesh.translation = light.position;
	if (light.visible) {
		renderMesh(light.mesh, camera);
	}
}