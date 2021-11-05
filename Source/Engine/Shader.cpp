#include "Engine/Shader.h"

ShaderLoaderInfo ShaderLoader;

std::vector<std::string> shaderFiles = {
	"./Resources/Shader/default.vert",
	"./Resources/Shader/default.frag",

	"./Resources/Shader/material.vert",
	"./Resources/Shader/material.frag",

	"./Resources/Shader/interface.vert",
	"./Resources/Shader/interface.frag",
};

void loadShaders() {
	for (size_t i = 0; i < shaderFiles.size(); i += 2) {
		GLuint vertShader = compileShader(shaderFiles[i]);
		GLuint fragShader = compileShader(shaderFiles[i + 1]);
		GLuint shader = createProgram(vertShader, fragShader);

		size_t i1 = shaderFiles[i].rfind("/");
		size_t i2 = shaderFiles[i].rfind(".");

		std::string name = shaderFiles[i].substr(0, i2).substr(i1 + 1, shaderFiles[i].size());

		ShaderInfo s;
		s.handle = shader;
		s.name = name;

		ShaderLoader.shaders.emplace(s.name, s);
	}
}

ShaderInfo getShader(std::string name) {
	return ShaderLoader.shaders[name];
}


std::string readFileContents(std::string filePath) {
	std::ifstream in(filePath.c_str(), std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return contents;
	}
	throw(errno);
}

std::string getExtension(std::string filePath) {
	std::size_t pos = filePath.rfind('.');

	if (pos != std::string::npos) {
		return filePath.substr(pos);
	}

	return "";
}

GLuint compileShader(std::string filePath) {
	std::string content = readFileContents(filePath);
	const char* source = content.c_str();
	std::string extension = getExtension(filePath);

	GLuint handle;
	if (extension == ".vert") {
		handle = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (extension == ".frag") {
		handle = glCreateShader(GL_FRAGMENT_SHADER);
	}
	else {
		std::cout << "Unsupported shader file " << filePath << std::endl;
		return NULL;
	}

	glShaderSource(handle, 1, &source, NULL);
	glCompileShader(handle);

	GLint hasCompiled;
	glGetShaderiv(handle, GL_COMPILE_STATUS, &hasCompiled);

	if (hasCompiled == GL_FALSE) {
		char info[1024];

		glGetShaderInfoLog(handle, 1024, NULL, info);
		std::cout << "SHADER_COMPILATION_ERROR for: " << filePath << "\n" << info << std::endl;

		return NULL;
	}

	return handle;
}


GLuint createProgram(GLuint vertexShader, GLuint fragmentShader) {
	GLuint handle = glCreateProgram();

	glAttachShader(handle, vertexShader);
	glAttachShader(handle, fragmentShader);

	glLinkProgram(handle);

	GLint hasCompiled;
	glGetShaderiv(handle, GL_COMPILE_STATUS, &hasCompiled);

	if (hasCompiled == GL_FALSE) {
		char info_log[1024];

		glGetProgramInfoLog(handle, 1024, NULL, info_log);
		std::cout << "PROGRAM_LINKING_ERROR for: " << "\n" << info_log << std::endl;

		return NULL;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return handle;
}