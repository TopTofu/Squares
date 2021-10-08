#include <Engine/Render.h>

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
	glfwSwapInterval(1);
}




void renderMesh(Mesh& mesh, Camera& camera) {
	glUseProgram(mesh.shader);

	glBindVertexArray(mesh.vao);

	glm::mat4 cameraMatrix = getCameraMatrix(camera);
	glUniformMatrix4fv(glGetUniformLocation(mesh.shader, "camera"), 1, GL_FALSE, glm::value_ptr(cameraMatrix));

	glm::mat4 transl = glm::mat4(1.0f);
	glm::mat4 rot = glm::mat4(1.0f);
	glm::mat4 sca = glm::mat4(1.0f);

	transl = glm::translate(transl, mesh.translation);
	rot = glm::mat4_cast(mesh.rotation);
	sca = glm::scale(sca, mesh.scale);

	// this is probably slower than multiplying in shader
	glm::mat4 transform = transl * rot * sca;

	glUniformMatrix4fv(glGetUniformLocation(mesh.shader, "transform"), 1, GL_FALSE, glm::value_ptr(transform));

	glDrawElements(mesh.primitive, mesh.indices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}




