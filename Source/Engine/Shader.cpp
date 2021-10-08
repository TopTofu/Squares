#include "Engine/Shader.h"

std::string readFileContents(const char* filePath) {
	std::ifstream in(filePath, std::ios::binary);
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

std::string getExtension(const char* filePath) {
	std::string path = filePath;
	std::size_t pos = path.rfind('.');

	if (pos != std::string::npos) {
		return path.substr(pos);
	}

	return "";
}


GLuint compileShader(const char* filePath) {
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