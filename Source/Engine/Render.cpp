#include <Engine/Render.h>
#include <Engine\Light.h>

void initOpenGL(GLFWwindow* window, int width, int height) {
	glfwMakeContextCurrent(window);
	gladLoadGL();

	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_MULTISAMPLE);

	/*glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);*/

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// vsync
	glfwSwapInterval(0);
}


void renderMesh(Mesh& mesh, Camera& camera, glm::mat4 parentTransform) {
	glUseProgram(mesh.shader);

	if (mesh.texture != 0) {
		glBindTexture(GL_TEXTURE_2D, mesh.texture->id);
		glUniform1i(glGetUniformLocation(mesh.shader, "Textured"), 1);
	}
	else {
		glUniform1i(glGetUniformLocation(mesh.shader, "Textured"), 0);
	}

	glBindVertexArray(mesh.vao);

	glm::mat4 cameraMatrix = getCameraMatrix(camera);
	glUniformMatrix4fv(glGetUniformLocation(mesh.shader, "camera"), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
	glUniform3fv(glGetUniformLocation(mesh.shader, "viewPos"), 1, glm::value_ptr(camera.position));

	glm::mat4 transl = glm::mat4(1.0f);
	glm::mat4 rot = glm::mat4(1.0f);
	glm::mat4 sca = glm::mat4(1.0f);

	transl = glm::translate(transl, mesh.translation);
	rot = glm::mat4_cast(mesh.rotation);
	sca = glm::scale(sca, mesh.scale);

	glm::mat4 transform = transl * rot * sca;
	transform = parentTransform * transform;
	glUniformMatrix4fv(glGetUniformLocation(mesh.shader, "transform"), 1, GL_FALSE, glm::value_ptr(transform));

	glUniform3fv(glGetUniformLocation(mesh.shader, "material.ambient"), 1, glm::value_ptr(mesh.material.ambient));
	glUniform3fv(glGetUniformLocation(mesh.shader, "material.diffuse"), 1, glm::value_ptr(mesh.material.diffuse));
	glUniform3fv(glGetUniformLocation(mesh.shader, "material.specular"), 1, glm::value_ptr(mesh.material.specular));
	glUniform1i(glGetUniformLocation(mesh.shader, "material.shininess"), mesh.material.specularExponent);
	glUniform1f(glGetUniformLocation(mesh.shader, "material.opaqueness"), mesh.material.opaqueness);

	glDrawElements(mesh.primitive, mesh.indices.size(), GL_UNSIGNED_INT, 0);

	glUseProgram(0);
	glBindVertexArray(0);
}


void renderModel(Model& model, Camera& camera) {
	glm::mat4 transl = glm::mat4(1.0f);
	glm::mat4 rot = glm::mat4(1.0f);
	glm::mat4 sca = glm::mat4(1.0f);

	transl = glm::translate(transl, model.translation);
	rot = glm::mat4_cast(model.rotation);
	sca = glm::scale(sca, model.scale);

	glm::mat4 t = transl * rot * sca;

	for (Mesh& mesh : model.meshes) {
		renderMesh(mesh, camera, t);
	}
}


