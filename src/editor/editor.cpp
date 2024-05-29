#include "editor.h"
#include "core/window.h"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_opengl3_loader.h>

#include <cstdio>

// Public functions
/////////////////////////////////////////////////////////////////////////////////
void editor_init() {
#ifdef EDITOR_ACTIVE 
  // Set up ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO io = ImGui::GetIO(); (void)io;

  // Setting context flags
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  // Dark mode WOOOOOOOAH! 
  ImGui::StyleColorsDark();

  // Setting up the glfw backend
  if(!ImGui_ImplGlfw_InitForOpenGL(window_get_handle(), true)) {
    fprintf(stderr, "[ERROR]: Failed to initialize GLFW for ImGui");
  }
  
  // Setting up the opengl backend
  if(!ImGui_ImplOpenGL3_Init("#version 460 core")) {
    fprintf(stderr, "[ERROR]: Failed to initialize OpenGL for ImGui");
  }
#endif
}

void editor_shutdown() {
#ifdef EDITOR_ACTIVE 
  ImGui_ImplGlfw_Shutdown();
  ImGui_ImplOpenGL3_Shutdown();
  ImGui::DestroyContext();
#endif
}

void editor_begin() {
#ifdef EDITOR_ACTIVE 
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
#endif
}

void editor_end() {
#ifdef EDITOR_ACTIVE 
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
}
/////////////////////////////////////////////////////////////////////////////////
