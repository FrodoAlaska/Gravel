#include "app.h"
#include "core/input.h"
#include "core/event.h"
#include "graphics/renderer.h"
#include "graphics/renderer2d.h"
#include "graphics/camera.h"

#include <glm/glm.hpp>

// App
/////////////////////////////////////////////////////////////////////////////////
struct App {
  Camera camera;
};

static App s_app;
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
bool app_init(void* user_data) {
  s_app.camera = camera_create(glm::vec3(10.0f, 0.0f, 10.0f), glm::vec3(-3.0f, 0.0f, 0.0f));

  return true;
}

void app_shutdown(void* user_data) {
}

void app_update(void* user_data) {
  if(input_key_pressed(KEY_ESCAPE)) {
    event_dispatch(EVENT_GAME_QUIT, EventDesc{});
  }
}

void app_render(void* user_data) {
  renderer_clear(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
  // editor_begin();

  renderer_begin(&s_app.camera);
  renderer_end();
  
  renderer2d_begin();
  renderer2d_end();
 
  // editor_end();
  renderer_present();
}
/////////////////////////////////////////////////////////////////////////////////
