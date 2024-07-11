cmake_minimum_required(VERSION 3.27)
project(Gravel)

add_subdirectory(libs/GLFW)
add_subdirectory(libs/glm)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(ENGINE_SRC_DIR ${CMAKE_SOURCE_DIR}/src/engine)
set(APP_SRC_DIR ${CMAKE_SOURCE_DIR}/src/app)
set(EDITOR_SRC_DIR ${CMAKE_SOURCE_DIR}/src/editor)
set(LIBS_DIR ${CMAKE_SOURCE_DIR}/libs/)

set(BUILD_FLAGS GLFW_INCLUDE_NONE APP_DEBUG EDITOR_ACTIVE)

set(ENGINE_SOURCES 
  # Core
  ${ENGINE_SRC_DIR}/core/window.cpp
  ${ENGINE_SRC_DIR}/core/input.cpp
  ${ENGINE_SRC_DIR}/core/event.cpp
  ${ENGINE_SRC_DIR}/core/clock.cpp
  ${ENGINE_SRC_DIR}/core/engine.cpp
  
  # Audio
  ${ENGINE_SRC_DIR}/audio/audio_system.cpp
  
  # Graphics
  ${ENGINE_SRC_DIR}/graphics/camera.cpp
  ${ENGINE_SRC_DIR}/graphics/renderer.cpp
  ${ENGINE_SRC_DIR}/graphics/renderer2d.cpp
  ${ENGINE_SRC_DIR}/graphics/shader.cpp

  # Math
  ${ENGINE_SRC_DIR}/math/rand.cpp
  ${ENGINE_SRC_DIR}/math/transform.cpp
  
  # Resources
  ${ENGINE_SRC_DIR}/resources/resource_manager.cpp
  ${ENGINE_SRC_DIR}/resources/texture.cpp
  ${ENGINE_SRC_DIR}/resources/font.cpp
  ${ENGINE_SRC_DIR}/resources/mesh.cpp
  ${ENGINE_SRC_DIR}/resources/material.cpp
  ${ENGINE_SRC_DIR}/resources/model.cpp
  
  # UI
  ${ENGINE_SRC_DIR}/ui/ui_text.cpp
  ${ENGINE_SRC_DIR}/ui/ui_button.cpp
  ${ENGINE_SRC_DIR}/ui/ui_canvas.cpp
  
  # Physics
  ${ENGINE_SRC_DIR}/physics/collider.cpp
  ${ENGINE_SRC_DIR}/physics/physics_body.cpp
  ${ENGINE_SRC_DIR}/physics/physics_world.cpp
 
  # Utils
  ${ENGINE_SRC_DIR}/utils/utils.cpp
  ${ENGINE_SRC_DIR}/utils/utils_file.cpp
)

set(APP_SOURCES 
  # App core 
  ${APP_SRC_DIR}/app.cpp 
  ${APP_SRC_DIR}/main.cpp 
)

set(EDITOR_SOURCES 
  # Editor 
  ${EDITOR_SRC_DIR}/editor.cpp
)

set(LIBS_SOURCES 
  ${LIBS_DIR}/miniaudio/miniaudio.cpp
  ${LIBS_DIR}/stb_image/stb_image.cpp
  ${LIBS_DIR}/stb_truetype/stb_truetype.cpp
  ${LIBS_DIR}/glad/gl.c

  ${LIBS_DIR}/glad/gl.c
  
  ${LIBS_DIR}/imgui/imgui.cpp 
  ${LIBS_DIR}/imgui/imgui_demo.cpp 
  ${LIBS_DIR}/imgui/imgui_draw.cpp 
  ${LIBS_DIR}/imgui/imgui_tables.cpp 
  ${LIBS_DIR}/imgui/imgui_widgets.cpp 
  ${LIBS_DIR}/imgui/backends/imgui_impl_glfw.cpp 
  ${LIBS_DIR}/imgui/backends/imgui_impl_opengl3.cpp 
  
  ${LIBS_DIR}/tinyobjloader/tiny_obj_loader.cc
)

add_executable(${PROJECT_NAME} ${ENGINE_SOURCES} ${APP_SOURCES} ${EDITOR_SOURCES} ${LIBS_SOURCES})

file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

target_compile_definitions(${PROJECT_NAME} PRIVATE ${BUILD_FLAGS})
target_compile_options(${PROJECT_NAME} PRIVATE -lm -Wno-deprecated)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_include_directories(${PROJECT_NAME} PUBLIC BEFORE ${LIBS_DIR} ${SRC_DIR} ${ENGINE_SRC_DIR} ${APP_SRC_DIR} ${EDITOR_SRC_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
