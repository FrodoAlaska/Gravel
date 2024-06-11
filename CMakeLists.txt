cmake_minimum_required(VERSION 3.27)
project(Gravel)

add_subdirectory(libs/GLFW)
add_subdirectory(libs/glm)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_BUILD_TYPE Debug)

set(GRAVEL_SRC_DIR src/)
set(GRAVEL_LIBS_DIR libs/)
set(GRAVEL_BUILD_FLAGS GLFW_INCLUDE_NONE GRAVEL_DEBUG EDITOR_ACTIVE)

set(GRAVEL_SOURCES 
  # Core
  ${GRAVEL_SRC_DIR}/core/window.cpp
  ${GRAVEL_SRC_DIR}/core/input.cpp
  ${GRAVEL_SRC_DIR}/core/event.cpp
  ${GRAVEL_SRC_DIR}/core/clock.cpp
  ${GRAVEL_SRC_DIR}/core/engine.cpp
  ${GRAVEL_SRC_DIR}/main.cpp
  ${GRAVEL_SRC_DIR}/app.cpp
  
  # Audio
  ${GRAVEL_SRC_DIR}/audio/audio_system.cpp
  
  # Graphics
  ${GRAVEL_SRC_DIR}/graphics/camera.cpp
  ${GRAVEL_SRC_DIR}/graphics/renderer.cpp
  ${GRAVEL_SRC_DIR}/graphics/renderer2d.cpp
  ${GRAVEL_SRC_DIR}/graphics/shader.cpp

  # Math
  ${GRAVEL_SRC_DIR}/math/rand.cpp
  
  # Components
  ${GRAVEL_SRC_DIR}/components/transform.cpp
  ${GRAVEL_SRC_DIR}/components/mesh.cpp
  
  # Editor
  ${GRAVEL_SRC_DIR}/editor/editor.cpp
  
  # Resources
  ${GRAVEL_SRC_DIR}/resources/resource_manager.cpp
  ${GRAVEL_SRC_DIR}/resources/texture.cpp
  ${GRAVEL_SRC_DIR}/resources/font.cpp
  
  # UI
  ${GRAVEL_SRC_DIR}/ui/ui_text.cpp
  ${GRAVEL_SRC_DIR}/ui/ui_button.cpp
  ${GRAVEL_SRC_DIR}/ui/ui_canvas.cpp
)

set(GRAVEL_LIBS 
  ${GRAVEL_LIBS_DIR}/miniaudio/miniaudio.cpp
  ${GRAVEL_LIBS_DIR}/stb_image/stb_image.cpp
  ${GRAVEL_LIBS_DIR}/stb_truetype/stb_truetype.cpp
  ${GRAVEL_LIBS_DIR}/glad/gl.c

  ${GRAVEL_LIBS_DIR}/glad/gl.c
  
  ${GRAVEL_LIBS_DIR}/imgui/imgui.cpp 
  ${GRAVEL_LIBS_DIR}/imgui/imgui_demo.cpp 
  ${GRAVEL_LIBS_DIR}/imgui/imgui_draw.cpp 
  ${GRAVEL_LIBS_DIR}/imgui/imgui_tables.cpp 
  ${GRAVEL_LIBS_DIR}/imgui/imgui_widgets.cpp 
  ${GRAVEL_LIBS_DIR}/imgui/backends/imgui_impl_glfw.cpp 
  ${GRAVEL_LIBS_DIR}/imgui/backends/imgui_impl_opengl3.cpp 
)

add_executable(${PROJECT_NAME} ${GRAVEL_SOURCES} ${GRAVEL_LIBS})

file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

target_compile_definitions(${PROJECT_NAME} PRIVATE ${GRAVEL_BUILD_FLAGS})
target_compile_options(${PROJECT_NAME} PRIVATE -lm)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_include_directories(${PROJECT_NAME} PUBLIC BEFORE ${GRAVEL_LIBS_DIR} ${GRAVEL_SRC_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC glfw glm)
