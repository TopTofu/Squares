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

Mesh loadOBJ(std::string filePath, bool buffer = true) {
	Mesh mesh;

	std::fstream file;
	file.open(filePath, std::ios::in);

	if (!file.is_open()) {
		printf("Failed to load model file [%s]\n", filePath.c_str());
		return mesh;
	}

	std::string line;

	std::vector<glm::vec3> normals = {};
	std::vector<glm::vec2> colorCoords = {};
	std::vector<glm::vec4> colors = {};
	std::vector<Material> mats;

	while (std::getline(file, line)) {
		if (line.empty()) {
			continue;
		}

		int spaceIndex = line.find(' ');
		if (spaceIndex == std::string::npos) continue;

		std::string type = line.substr(0, spaceIndex);
		line.erase(0, spaceIndex + 1);
		if (line.empty()) continue;
		if (type == "#") continue;

		if (type == "mtllib") {
			// material file
			std::string matPath = filePath.substr(0, filePath.rfind('/') + 1) + line;
			mats = loadMtl(matPath);
		}

		else if (type == "usemtl") {
			// material name

		}

		else if (type == "o") {
			// object name
		}

		else if (type == "g") {
			// group name
		}

		else if (type == "vn") {
			// normal
			std::vector<std::string> values = splitAt(line, " ");

			normals.push_back(glm::vec3(stof(values[0]), stof(values[1]), stof(values[2])));
		}

		else if (type == "vt") {
			// uv coords
			float u = 0.0f;
			float v = 0.0f;
			float w = 0.0f;

			std::vector<std::string> values = splitAt(line, " ");

			u = stof(values[0]);

			if (line.size() > 1) v = stof(values[1]);

			if (line.size() > 2) w = stof(values[2]);

			colorCoords.push_back({ u, v });
		}

		else if (type == "v") {
			// vertex
			std::vector<std::string> values = splitAt(line, " ");

			Vertex v;
			v.position = { stof(values[0]), stof(values[1]), stof(values[2]) };

			mesh.vertices.push_back(v);
		}

		else if ("f") {
			// faces
			std::vector<std::string> values = splitAt(line, "/ ");

			if (values.size() == 12) {
				int i0 = stoi(values[0]) - 1;
				int i1 = stoi(values[3]) - 1;
				int i2 = stoi(values[6]) - 1;
				int i3 = stoi(values[9]) - 1;

				mesh.indices.push_back(i0);
				mesh.indices.push_back(i1);
				mesh.indices.push_back(i2);

				mesh.indices.push_back(i0);
				mesh.indices.push_back(i2);
				mesh.indices.push_back(i3);

				mesh.vertices[i0].color = colors[(int)((colorCoords[stoi(values[1]) - 1].x) * colors.size())];
				mesh.vertices[i1].color = colors[(int)((colorCoords[stoi(values[4]) - 1].x) * colors.size())];
				mesh.vertices[i2].color = colors[(int)((colorCoords[stoi(values[7]) - 1].x) * colors.size())];
				mesh.vertices[i3].color = colors[(int)((colorCoords[stoi(values[10]) - 1].x) * colors.size())];

				mesh.vertices[i0].normal = normals[stoi(values[2]) - 1];
				mesh.vertices[i1].normal = normals[stoi(values[5]) - 1];
				mesh.vertices[i2].normal = normals[stoi(values[8]) - 1];
				mesh.vertices[i3].normal = normals[stoi(values[11]) - 1];
			}
		}
		
		else if ("s") {
			// smooth shading
		}

		else {
			printf("In file [%s] found unparsed line: %s\n", filePath, type + " " + line);
		}
	}

	file.close();

	mesh.primitive = GL_TRIANGLES;

	if (buffer) bufferMesh(mesh);

	return mesh;
}


std::vector<Material> loadMtl(std::string filePath) {
	std::fstream file;
	file.open(filePath, std::ios::in);
	std::vector<Material> mats = {};

	if (!file.is_open()) {
		printf("Failed to open material file %s.\n", filePath.c_str());
		return mats;
	}

	std::string line;

	while (std::getline(file, line)) {
		if (line.empty()) continue;

		int spaceIndex = line.find(' ');
		if (spaceIndex == std::string::npos) continue;

		std::string type = line.substr(0, spaceIndex);
		line.erase(0, spaceIndex + 1);
		if (line.empty()) continue;

		if (type == "newmtl") {} // starts new material, gives name

		else if (type == "#") {} // comment

		else if (type == "illum") {} // illumination mode

		else if (type == "Ka") {} // ambient color

		else if (type == "Kd") {} // diffuse color

		else if (type == "Ks") {} // specular color
		
		else if (type == "d") {} // opaqueness

		else if (type == "Ni") {} // optical density (refraction index)

		else if (type == "Ns") {} // specular exponent (range 0 - 1000)

		else printf("In file [%s] found unparsed line: %s\n", filePath, type + " " + line);
	}

	return mats;
}