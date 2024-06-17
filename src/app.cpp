#include "app.h"
#include "core/clock.h"
#include "graphics/camera.h"
#include "math/transform.h"
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

  f32 mesh_rotation = 0.0f;
  Mesh* meshes[MAX_DUDES][MAX_DUDES];
  Transform transforms[MAX_DUDES][MAX_DUDES];
  Transform model_transform;
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

  // s_app.canvas = ui_canvas_create(s_app.font);
  s_app.mat = material_load_default();
  s_app.mat->diffuse_map = s_app.txt;

  s_app.model = resources_add_model("cottage", "assets/models/cottage_home/cottage_obj.obj");
  // s_app.model = model_load("assets/models/little_pumpkin.obj");
  // s_app.model = model_load("assets/models/SittingBaby/baby.obj");
  // s_app.model = model_load("assets/models/backpack/backpack.obj");

  transform_create(&s_app.model_transform, glm::vec3(10.0f, 0.0f, 10.0f));

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
  
  // @TODO: ui_text_set_string(&s_app.canvas->texts[0], "GRAVEL");

  // s_app.mesh_rotation += 2.0f * gclock_delta_time();
  transform_rotate(&s_app.model_transform, s_app.mesh_rotation, glm::vec3(1.0f, 0.0f, 0.0f));
}

void app_render(void* user_data) {
  renderer_clear(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
  // editor_begin();

  renderer_begin(&s_app.camera);
  render_model(s_app.model_transform, s_app.model);
  renderer_end();

  // renderer2d_begin();
  // renderer2d_end();
 
  // editor_end();
  renderer_present();
}
/////////////////////////////////////////////////////////////////////////////////
