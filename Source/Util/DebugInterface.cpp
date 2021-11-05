#include <Util/DebugInterface.h>

DebugInterface Debug;


void initDebugInterface(GLFWwindow* window) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}


void updateDebugInterface(Light& light) {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	static double dt = Context.dt;
	static int fps = Context.fps;
	static int framesUntilUpdate = fps;

	if (framesUntilUpdate <= 0) {
		dt = Context.dt;
		fps = Context.fps;
		framesUntilUpdate = fps;
	}

	framesUntilUpdate--;

	ImGui::Begin("Window");
	ImGui::SliderFloat3("Light", (float*)&light.position, -2.0f, 20.0f);
	ImGui::Checkbox("light visible", &light.visible);
	ImGui::Checkbox("wireframe", &Debug.wireframe);
	ImGui::Text((std::to_string(fps) + " FPS").c_str());
	ImGui::Text((std::to_string(dt) + " ms").c_str());
	if (Interface.cellPicker.stuckObject.meshes.size() > 0) {
		ImGui::SliderFloat(".", (float*)&Interface.cellPicker.stuckObject.meshes[0].material.specularExponent, -1.0f, 1000.0f);
	}
	ImGui::End();

	if (Debug.wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

void renderDebugInterface() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}