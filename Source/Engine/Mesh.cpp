#include <Engine/Mesh.h>


Mesh getQuadMesh(glm::vec3 origin, glm::vec3 s0, glm::vec3 s1, glm::vec4 color, bool buffer) {
	Mesh mesh;

	Vertex v0;
	v0.position = origin;
	v0.color = color;
	Vertex v1;
	v1.position = origin + s0;
	v1.color = color;
	Vertex v2;
	v2.position = origin + s0 + s1;
	v2.color = color;
	Vertex v3;
	v3.position = origin + s1;
	v3.color = color;

	mesh.vertices.push_back(v0);
	mesh.vertices.push_back(v1);
	mesh.vertices.push_back(v2);
	mesh.vertices.push_back(v3);

	mesh.indices.push_back(0);
	mesh.indices.push_back(1);
	mesh.indices.push_back(2);

	mesh.indices.push_back(0);
	mesh.indices.push_back(2);
	mesh.indices.push_back(3);

	mesh.primitive = GL_TRIANGLES;

	if (buffer) bufferMesh(mesh);

	return mesh;
}

Mesh getCircleMesh(float r, int numSegements, glm::vec4 color) {
	Mesh mesh;

	for (int i = 0; i < numSegements; i++) {
		float theta = 2.0f * 3.14159f * float(i) / float(numSegements);

		float x = r * cosf(theta);
		float y = r * sinf(theta);

		Vertex v;
		v.position = glm::vec3(x, y, 0.0f);
		v.color = color;

		mesh.vertices.push_back(v);
		mesh.indices.push_back(i);
	}

	mesh.primitive = GL_LINE_LOOP;

	return mesh;
}

void bufferMesh(Mesh& mesh) {
	glDeleteVertexArrays(1, &mesh.vao);

	GLuint vao, vbo, ebo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), mesh.vertices.data(), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(GLuint), mesh.indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0); // position

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1); // uv

	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2); // color

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);

	mesh.vao = vao;
}

void translateMeshTo(Mesh& mesh, glm::vec3 destination) {
	mesh.translation = destination;
}

void translateMeshBy(Mesh& mesh, glm::vec3 offset) {
	mesh.translation += offset;
}

void scaleMeshTo(Mesh& mesh, glm::vec3 scale) {
	mesh.scale = scale;
}

void scaleMeshBy(Mesh& mesh, glm::vec3 scale) {
	mesh.scale *= scale;
}

void rotateMeshBy(Mesh& mesh, glm::vec3 axis, float degrees) {
	mesh.rotation = glm::rotate(mesh.rotation, glm::radians(degrees), axis);
}

