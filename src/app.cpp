#include "app.h"
#include "graphics/camera.h"
#include "resources/font.h"
#include "resources/texture.h"
#include "resources/resource_manager.h"
#include "graphics/renderer.h"
#include "graphics/renderer2d.h"
#include "graphics/color.h"
#include "core/input.h"
#include "core/event.h"
#include "ui/ui_text.h"
#include "ui/ui_button.h"

// App
/////////////////////////////////////////////////////////////////////////////////
struct App {
  Camera camera;
  Font* font;
  Texture* texture, *txt;

  UIText hello_text;
  UIButton play_button;
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

  ui_text_create(&s_app.hello_text, nullptr, "Gravel", 50.0f, UI_ANCHOR_TOP_CENTER, COLOR_WHITE);
  ui_button_create(&s_app.play_button, s_app.font, "PLAY", 50.0f, UI_ANCHOR_CENTER, COLOR_WHITE, COLOR_BLACK);

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
  // render_texture(s_app.txt, glm::vec2(1280 / 2, 720 / 2.0f), glm::vec2(512.0f, 512.0f));
  ui_text_render(&s_app.hello_text);
  ui_button_render(&s_app.play_button);
  renderer2d_end();
 
  // editor_end();
  renderer_present();
}
/////////////////////////////////////////////////////////////////////////////////
