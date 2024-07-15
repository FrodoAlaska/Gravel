#include "app.h"
#include "core/input.h"
#include "engine/core/clock.h"
#include "engine/graphics/renderer.h"
#include "engine/graphics/renderer2d.h"
#include "engine/graphics/camera.h"
#include "engine/physics/physics_world.h"
#include "engine/resources/font.h"
#include "editor/editor.h"
#include "physics/collider.h"
#include "physics/physics_body.h"
#include "resources/material.h"
#include "resources/mesh.h"

#include <glm/glm.hpp>

#include <string>

struct Player {
  PhysicsBody* body;
  BoxCollider collider;
  Mesh* mesh;

  void init(const glm::vec3& pos) {
    PhysicsBodyDesc body_desc {
      .position = pos,
      .type = PHYSICS_BODY_DYNAMIC, 
      .mass = 1.0f, 
      .is_active = true
    };

    body = physics_world_add_body(body_desc);
    collider = BoxCollider{.half_size = glm::vec3(0.5f)};
    mesh = mesh_create();
  }

  void update() {
    
  }

  void render() {
    render_mesh(body->transform, mesh);
  }
};

// App
/////////////////////////////////////////////////////////////////////////////////
struct App {
  Camera camera;
  Camera* current_cam;

  Player player;
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

  // Physics init 
  physics_world_create(glm::vec3(0.0f, 0.0f, 0.0f));
 
  s_app.player.init(glm::vec3(10.0f, 0.0f, 10.0f));
  
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
  s_app.player.update();
}

void app_render(void* user_data) {
  renderer_clear(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
  editor_begin();

  renderer_begin(s_app.current_cam);
  s_app.player.render(); 
  renderer_end();
  
  renderer2d_begin();
  renderer2d_end();
 
  editor_end();
  renderer_present();
}
/////////////////////////////////////////////////////////////////////////////////
