#include "app.h"
#include "core/clock.h"
#include "graphics/camera.h"
#include "resources/font.h"
#include "resources/material.h"
#include "resources/mesh.h"
#include "resources/model.h"
#include "resources/texture.h"
#include "resources/resource_manager.h"
#include "graphics/renderer.h"
#include "graphics/renderer2d.h"
#include "graphics/color.h"
#include "core/input.h"
#include "core/event.h"
#include "ui/ui_canvas.h"

#include <cstdio>

const int MAX_DUDES = 1;

// App
/////////////////////////////////////////////////////////////////////////////////
struct App {
  Camera camera;
  Font* font;
  Texture* texture, *txt;

  UICanvas* canvas;
  UIText title;

  f32 mesh_rotation;
  Mesh* meshes[MAX_DUDES][MAX_DUDES];
  Transform transforms[MAX_DUDES][MAX_DUDES];
  Material* mat;

  Model* model;
};

static App s_app;
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
bool app_init(void* user_data) {
  s_app.font = resources_add_font("font/bit5x3.ttf", "regular_font");
  s_app.texture = resources_add_texture("logo_texture", "textures/mg_logo.png");
  s_app.txt = resources_add_texture("damage", "textures/mid_finger.jpeg");
  s_app.camera = camera_create(glm::vec3(10.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, -3.0f));
  input_cursor_show(false);

  renderer2d_set_default_font(s_app.font);

  s_app.canvas = ui_canvas_create(s_app.font);
  s_app.mat = material_load_default();
  s_app.mat->diffuse_map[0] = s_app.txt;

  s_app.mesh_rotation = 0.0f;
  for(u32 i = 0; i < MAX_DUDES; i++) {
    for(u32 j = 0; j < MAX_DUDES; j++) {
      s_app.meshes[i][j] = mesh_create();
      transform_create(&s_app.transforms[i][j], glm::vec3(10.0f, 0.0f, 10.0f));
    }
  }

  ui_canvas_push_text(s_app.canvas, "Gravel", 50.0f, COLOR_WHITE, UI_ANCHOR_TOP_CENTER);

  ui_canvas_begin(s_app.canvas, glm::vec2(0.0f, 70.0f), UI_ANCHOR_CENTER);
  ui_canvas_push_button(s_app.canvas, "PLAY", 40.0f, COLOR_WHITE, COLOR_BLACK, nullptr, nullptr);
  ui_canvas_push_button(s_app.canvas, "SETTINGS", 40.0f, COLOR_WHITE, COLOR_BLACK, nullptr, nullptr);
  ui_canvas_push_button(s_app.canvas, "QUIT", 40.0f, COLOR_WHITE, COLOR_BLACK, nullptr, nullptr);
  ui_canvas_end(s_app.canvas);

  s_app.model = model_load("assets/models/cottage_home", glm::vec3(10.0f, 0.0f, 10.0f));

  return true;
}

void app_shutdown(void* user_data) {
  ui_canvas_destroy(s_app.canvas);
}

void app_update(void* user_data) {
  if(input_key_pressed(KEY_ESCAPE)) {
    event_dispatch(EVENT_GAME_QUIT, EventDesc{});
  }

  camera_update(&s_app.camera);
  camera_move(&s_app.camera);
  
  // @TODO: ui_text_set_string(&s_app.canvas->texts[0], "GRAVEL");

  s_app.mesh_rotation += 2.0f * gclock_delta_time();

  printf("[INFO]: FPS = %f\n", gclock_fps());
}

void app_render(void* user_data) {
  renderer_clear(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
  // editor_begin();

  renderer_begin(&s_app.camera);
  // render_model(s_app.model);

  transform_rotate(&s_app.transforms[0][0], s_app.mesh_rotation, glm::vec3(1.0f));
  render_mesh(s_app.transforms[0][0], s_app.meshes[0][0], s_app.mat);
  // render_cube(glm::vec3(10.0f, 0.0f, 10.0f),  glm::vec3(1.0f, 1.0f, 1.0f), 45.0f, COLOR_WHITE);
  
  // for(u32 i = 0; i < MAX_DUDES; i++) {
  //   for(u32 j = 0; j < MAX_DUDES; j++) {
  //     render_cube(s_app.transforms[i][j].position, glm::vec3(1.0f), COLOR_WHITE);
  //   }
  // }
  renderer_end();

  // renderer2d_begin();
  // render_quad(glm::vec2(150.0f, 120.0f), glm::vec2(256.0f, 50.0f), glm::vec4(1.0f));
  // render_texture(s_app.texture, glm::vec2(100.0f, 100.0f), glm::vec2(128.0f, 128.0f));
  // render_texture(s_app.txt, glm::vec2(1280 / 2, 720 / 2.0f), glm::vec2(512.0f, 512.0f));
  // ui_canvas_render(s_app.canvas); 
  // renderer2d_end();
 
  // editor_end();
  renderer_present();
}
/////////////////////////////////////////////////////////////////////////////////
