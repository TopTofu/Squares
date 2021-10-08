#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <glad/glad.h>



std::string readFileContents(std::string filePath);
std::string getExtension(std::string filePath);
GLuint compileShader(const char* filePath);
GLuint createProgram(GLuint vertexShader, GLuint fragmentShader);
