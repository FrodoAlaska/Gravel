#include "app.h"
#include "core/input.h"
#include "engine/graphics/renderer.h"
#include "engine/graphics/renderer2d.h"
#include "engine/graphics/camera.h"
#include "editor/editor.h"
#include "resources/cubemap.h"

#include <glm/glm.hpp>

/*
 * An example Gravel application. 
 * The 'engine.cpp' file uses the function pointer of this application to 
 * initialize, update, render, and shutdown the application. 
 * The function pointers are implemented here. 
 *
 * In this example, the application is a static variable where all of the functions can 
 * access freely. This is done just for simplicity sake. However, it would be better to make the 
 * application the engine's responsibility to declare and keep around. You can pass around the application 
 * in the 'user_data' parametar of each function pointer. You will have to convert the 'void*' to your 
 * desired application structure. 
 */

// App
/////////////////////////////////////////////////////////////////////////////////
struct App {
  Camera camera;
  Camera* current_cam;

  CubeMap* cubemap;
};

static App s_app;
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
bool app_init(void* user_data) {
  // Disable the cursor
  input_cursor_show(false);

  // Camera init 
  s_app.camera = camera_create(glm::vec3(1.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, -3.0f));
  
  // Editor init
  editor_init(glm::vec3(10.0f, 5.0f, 10.0f), glm::vec3(0.0f, 1.0f, -3.0f), false);

  // This can be switched between the game camera and editor camera
  s_app.current_cam = &s_app.camera;

  s_app.cubemap = cubemap_load("assets/cubemaps/desert_cubemap/");

  return true;
}

void app_shutdown(void* user_data) {
  cubemap_unload(s_app.cubemap);

  editor_shutdown();
}

void app_update(void* user_data) {
  camera_update(s_app.current_cam);
  camera_move(s_app.current_cam);
}

void app_render(void* user_data) {
  renderer_clear(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
  editor_begin();

  renderer_begin(s_app.current_cam);
  render_cubemap(s_app.cubemap, s_app.current_cam);
  renderer_end();
  
  renderer2d_begin();
  renderer2d_end();
 
  editor_end();
  renderer_present();
}
/////////////////////////////////////////////////////////////////////////////////
