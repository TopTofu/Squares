#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


GLFWwindow* initWindow(int width, int height);
void framebufferResizeCallback(GLFWwindow* window, int width, int height);