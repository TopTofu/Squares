#pragma once

#include <string>

#include "Engine/Light.h"
#include "Engine/Context.h"
#include "Game/Interface.h"

#include "Util/imgui/imgui.h"
#include "Util/imgui/imgui_impl_opengl3.h"
#include "Util/imgui/imgui_impl_glfw.h"


struct DebugInterface {
	bool wireframe = false;
};


extern DebugInterface Debug;


void initDebugInterface(GLFWwindow* window);
void updateDebugInterface(Light& light);
void renderDebugInterface();
