#include "app.h"
#include "core/clock.h"
#include "graphics/renderer.h"
#include "graphics/renderer2d.h"
#include "graphics/camera.h"
#include "physics/physics_world.h"
#include "resources/font.h"
#include "editor/editor.h"

#include <glm/glm.hpp>

#include <string>

// App
/////////////////////////////////////////////////////////////////////////////////
struct App {
  Camera camera;
  Camera* current_cam;

  Font* font;
};

static App s_app;
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
bool app_init(void* user_data) {
  // Loading the default font
  s_app.font = font_load("assets/font/bit5x3.ttf", 256.0f);
  renderer2d_set_default_font(s_app.font);

  // Camera init 
  s_app.camera = camera_create(glm::vec3(10.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, -3.0f));
  
  // Editor init
  editor_init(glm::vec3(10.0f, 5.0f, 10.0f), glm::vec3(0.0f, 1.0f, -3.0f), false);

  // This can be switched between the game camera and editor camera
  s_app.current_cam = &s_app.camera;

  physics_world_create(glm::vec3(0.0f, 0.0f, 0.0f));

  return true;
}

void app_shutdown(void* user_data) {
  physics_world_destroy();
  editor_shutdown();
}

void app_update(void* user_data) {
  camera_update(s_app.current_cam);
  camera_move(s_app.current_cam);

  physics_world_update(gclock_delta_time());
}

void app_render(void* user_data) {
  renderer_clear(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
  editor_begin();

  renderer_begin(s_app.current_cam);
  renderer_end();
  
  renderer2d_begin();
  renderer2d_end();
 
  editor_end();
  renderer_present();
}
/////////////////////////////////////////////////////////////////////////////////
