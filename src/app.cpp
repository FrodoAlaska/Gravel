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
  Texture* texture, *txt;
};

static App s_app;
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
bool app_init(void* user_data) {
  s_app.font = resources_add_font("font/bit5x3.ttf", "regular_font");
  s_app.texture = resources_add_texture("logo_texture", "textures/mg_logo.png");
  s_app.txt = resources_add_texture("damage", "textures/dnukem.jpg");
  s_app.camera = camera_create(glm::vec3(10.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, -3.0f));

  renderer2d_set_default_font(s_app.font);

  return true;
}

void app_shutdown(void* user_data) {
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
  // render_quad(glm::vec2(150.0f, 120.0f), glm::vec2(256.0f, 50.0f), glm::vec4(1.0f));
  // render_texture(s_app.texture, glm::vec2(100.0f, 100.0f), glm::vec2(128.0f, 128.0f));
  // render_texture(s_app.txt, glm::vec2(300.0f, 100.0f), glm::vec2(256.0f, 256.0f));
  render_text(50.0f, "EVA is a fucking whore", glm::vec2(100.0f, 100.0f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
  renderer2d_end();
 
  // editor_end();
  renderer_present();
}
/////////////////////////////////////////////////////////////////////////////////
