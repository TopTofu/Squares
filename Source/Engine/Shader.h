#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>



std::string readFileContents(std::string filePath);
std::string getExtension(std::string filePath);
GLuint compileShader(const char* filePath);
GLuint createProgram(GLuint vertexShader, GLuint fragmentShader);
