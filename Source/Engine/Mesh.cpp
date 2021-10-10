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

	mesh.indices.push_back(1);
	mesh.indices.push_back(0);
	mesh.indices.push_back(2);

	mesh.indices.push_back(2);
	mesh.indices.push_back(0);
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

Mesh getQubeMesh(float size, bool buffer) {
	Mesh m;
	m.vertices = std::vector<Vertex>{
		Vertex{ glm::vec3(-0.5, -0.5, -0.5), {0,0}, {1,1,1,1} },
		Vertex{ glm::vec3(0.5,  -0.5, -0.5), {0,0}, {1,1,1,1} },
		Vertex{ glm::vec3(0.5,   0.5, -0.5), {0,0}, {1,1,1,1} },
		Vertex{ glm::vec3(-0.5,  0.5, -0.5), {0,0}, {1,1,1,1} },
		Vertex{ glm::vec3(-0.5,	-0.5,  0.5), {0,0}, {1,1,1,1} },
		Vertex{ glm::vec3(0.5,	-0.5,  0.5), {0,0}, {1,1,1,1} },
		Vertex{ glm::vec3(0.5,   0.5,  0.5), {0,0}, {1,1,1,1} },
		Vertex{ glm::vec3(-0.5,  0.5,  0.5), {0,0}, {1,1,1,1} },
	};

	m.indices = std::vector<GLuint>{
			0, 1, 2,
			0, 2, 3,

			4, 1, 0,
			4, 5, 1,

			2, 1, 5,
			2, 5, 6,

			7, 0, 3,
			7, 4, 0,

			6, 5, 4,
			6, 4, 7,

			3, 2, 6,
			3, 6, 7
	};

	if (buffer) bufferMesh(m);

	m.scale = { size, size, size };

	return m;
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

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(9 * sizeof(float)));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);

	mesh.vao = vao;
}

void bufferModel(Model& model) {
	for (Mesh& mesh : model.meshes) {
		bufferMesh(mesh);
	}
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

void translateModelTo(Model& model, glm::vec3 destination) {
	model.translation = destination;
}

void translateModelBy(Model& model, glm::vec3 offset) {
	model.translation += offset;
}

void scaleModelTo(Model& model, glm::vec3 scale) {
	model.scale = scale;
}

void scaleModelBy(Model& model, glm::vec3 scale) {
	model.scale *= scale;
}

void rotateModelBy(Model& model, glm::vec3 axis, float degrees) {
	model.rotation = glm::rotate(model.rotation, glm::radians(degrees), axis);
}

Model loadOBJ(std::string filePath, bool buffer) {
	Model model;
	model.filePath = filePath;

	model.name = filePath.substr(0, filePath.find('.')).substr(filePath.rfind('/') + 1, filePath.size());

	std::fstream file;
	file.open(filePath, std::ios::in);

	if (!file.is_open()) {
		printf("Failed to load model file [%s]\n", filePath.c_str());
		return model;
	}

	std::string line;

	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec4> colors;
	std::vector<Material> materials;

	Mesh currentMesh;

	int vCount = 0;

	while (std::getline(file, line)) {
		if (line.empty()) {
			continue;
		}

		size_t spaceIndex = line.find(' ');
		if (spaceIndex == std::string::npos) continue;

		std::string type = line.substr(0, spaceIndex);
		line.erase(0, spaceIndex + 1);

		if (line.empty()) continue;
		if (type == "#") continue;

		if (type == "mtllib") {
			// material file
			std::string matPath = filePath.substr(0, filePath.rfind('/') + 1) + line;
			materials = loadMtl(matPath);
		}

		else if (type == "usemtl") {
			// material name
			for (Material mat : materials) {
				if (mat.name == line) {
					if (currentMesh.vertices.size() > 0) {
						model.meshes.push_back(currentMesh);
						currentMesh = {};
						vCount = 0;
					}

					currentMesh.material = mat;
					break;
				}
			}
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

			if (values.size() > 1) v = stof(values[1]);

			if (values.size() > 2) w = stof(values[2]);

			texCoords.push_back({ u, v });
		}

		else if (type == "v") {
			// vertex
			std::vector<std::string> values = splitAt(line, " ");

			glm::vec3 v = { stof(values[0]), stof(values[1]), stof(values[2]) };

			positions.push_back(v);
		}

		else if (type == "f") {
			// faces (pos/uv/normal) - indices

			/*
				f 1 2 3					lines
				f 3/1 4/2 5/3			pos/uv
				f 6/4/1 3/5/3 7/6/5		pos/uv/normal
				f 7//1 8//2 9//3		pos//normal
			*/

			std::vector<std::string> values = splitAt(line, "/ ");

			int valuesPerIndex = splitAt(splitAt(line, " ")[0], "/").size();

			size_t slashIndex = line.rfind('/');
			if (valuesPerIndex == 1) {
				throw(errno);
			}
			if (valuesPerIndex == 2) {
				size_t slashIndex = line.rfind('/') - 1;
				if (line[slashIndex + 1] == '/') {
					// pos//normal
					for (size_t i = 0; i < values.size(); i += 2) {
						size_t posI = stol(values[i]) - 1; // indices in file start with 1
						size_t normI = stol(values[i + 1]) - 1;

						Vertex v;
						v.position = positions[posI];
						v.normal = normals[normI];
						v.color = glm::vec4(currentMesh.material.diffuse, 1.0f);

						currentMesh.vertices.push_back(v);

						currentMesh.indices.push_back(vCount);
						vCount++;
					}
				}
				else {
					// pos/uv
					for (size_t i = 0; i < values.size(); i += 2) {
						size_t posI = stol(values[i]) - 1; // indices in file start with 1
						size_t uvI = stol(values[i + 1]) - 1;

						Vertex v;
						v.position = positions[posI];
						v.uv = texCoords[uvI];
						v.color = glm::vec4(currentMesh.material.diffuse, 1.0f);

						currentMesh.vertices.push_back(v);

						currentMesh.indices.push_back(vCount);
						vCount++;
					}
				}
			}
			if (valuesPerIndex == 3) {
				/*pos/uv/normal*/

				for (size_t i = 0; i < values.size(); i += 3) {
					size_t posI = stol(values[i]) - 1; // indices in file start with 1
					size_t uvI = stol(values[i + 1]) - 1;
					size_t normI = stol(values[i + 2]) - 1;

					Vertex v;
					v.position = positions[posI];
					v.normal = normals[normI];
					v.uv = texCoords[uvI];
					v.color = glm::vec4(currentMesh.material.diffuse, 1.0f);

					currentMesh.vertices.push_back(v);

					currentMesh.indices.push_back(vCount);
					vCount++;
				}
			}
		}

		else if (type == "s") {
			// smooth shading
		}

		else {
			printf("In file [%s] found unparsed line: %s\n", filePath.c_str(), (type + " " + line).c_str());
		}
	}

	model.meshes.push_back(currentMesh);

	if (buffer) bufferModel(model);

	file.close();

	return model;
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
	Material currentMat;
	bool first = true;

	while (std::getline(file, line)) {
		if (line.empty()) continue;

		size_t spaceIndex = line.find(' ');
		if (spaceIndex == std::string::npos) continue;

		std::string type = line.substr(0, spaceIndex);
		line.erase(0, spaceIndex + 1);
		if (line.empty()) continue;

		if (type == "newmtl") {
			// starts new material, gives name
			if (!first) {
				mats.push_back(currentMat);
				currentMat = {};
			}
			else first = false;

			currentMat.name = line;
		}

		else if (type == "#") {} // comment

		else if (type == "illum") {
			// illumination mode
			currentMat.illuminationMode = IlluminationMode(stoi(line));
		}

		else if (type == "Ka") {
			// ambient color
			std::vector<std::string> values = splitAt(line, " ");
			currentMat.ambient = { stof(values[0]), stof(values[1]), stof(values[2]) };
		}

		else if (type == "Kd") {
			// diffuse color
			std::vector<std::string> values = splitAt(line, " ");
			currentMat.diffuse = { stof(values[0]), stof(values[1]), stof(values[2]) };
		}

		else if (type == "Ks") {
			// specular color
			std::vector<std::string> values = splitAt(line, " ");
			currentMat.specular = { stof(values[0]), stof(values[1]), stof(values[2]) };
		}

		else if (type == "d") {
			// opaqueness
			currentMat.opaqueness = stof(line);
		}

		else if (type == "Ni") {
			// optical density (refraction index)
			currentMat.refractionIndex = stof(line);
		} 

		else if (type == "Ns") {
			// specular exponent (range 0 - 1000)
			currentMat.specularExponent = stoi(line);
		}

		else printf("In file [%s] found unparsed line: %s\n", filePath.c_str(), (type + " " + line).c_str());
	}

	mats.push_back(currentMat);

	return mats;
}
