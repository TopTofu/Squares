#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include <Engine/Camera.h>
#include <Engine/Mesh.h>



void initOpenGL(GLFWwindow* window, int width, int height);

void renderMesh(Mesh& mesh, Camera& camera);
void renderModel(Model& model, Camera& camera);





