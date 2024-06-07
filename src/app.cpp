#include "app.h"
#include "graphics/camera.h"
#include "resources/font.h"
#include "resources/texture.h"
#include "resources/resource_manager.h"
#include "graphics/renderer.h"
#include "graphics/renderer2d.h"
#include "core/input.h"
#include "core/event.h"

// App
/////////////////////////////////////////////////////////////////////////////////
struct App {
  Camera camera;
  Font* font;
  Texture* texture;
};

static App s_app;
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
bool app_init(void* user_data) {
  s_app.font = font_load("assets/font/HeavyDataNerdFont.ttf", 256);
  s_app.texture = resources_add_texture("logo_texture", "textures/mg_logo.png");
  s_app.camera = camera_create(glm::vec3(10.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, -3.0f));

  return true;
}

void app_shutdown(void* user_data) {
  font_unload(s_app.font);
}

void app_update(void* user_data) {
  if(input_key_pressed(KEY_ESCAPE)) {
    event_dispatch(EVENT_GAME_QUIT, EventDesc{});
  }

  camera_update(&s_app.camera);
  camera_move(&s_app.camera);
}

void app_render(void* user_data) {
  renderer_clear(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
  // editor_begin();

  // renderer_begin(&s_app.camera);
  // renderer_end();

  renderer2d_begin();
  render_text(s_app.font, 50.0f, "Hello, world. Wtf is going on?", glm::vec2(100.0f, 100.0f), glm::vec4(1.0f, 0.0f, 0.5f, 1.0f));
  // render_texture(s_app.texture, glm::vec2(200.0f, 200.0f), glm::vec2(128.0f, 128.0f));
  renderer2d_end();
 
  // editor_end();
  renderer_present();
}
/////////////////////////////////////////////////////////////////////////////////
