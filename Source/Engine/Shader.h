#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <vector>
#include <map>

struct ShaderInfo {
	GLuint handle;
	std::string name;
};

struct ShaderLoaderInfo {
	std::map<std::string, ShaderInfo> shaders;
};

extern ShaderLoaderInfo ShaderLoader;

void loadShaders();
std::string readFileContents(std::string filePath);
std::string getExtension(std::string filePath);
GLuint compileShader(std::string filePath);
GLuint createProgram(GLuint vertexShader, GLuint fragmentShader);
ShaderInfo getShader(std::string name);