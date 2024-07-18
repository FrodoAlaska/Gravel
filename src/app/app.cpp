#include "app.h"
#include "core/event.h"
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
#include "utils/utils.h"

#include <glm/glm.hpp>

#include <cstdio>
#include <string>

struct Entity {
  PhysicsBody* body;
  BoxCollider collider;
  Mesh* mesh;

  void init(const glm::vec3& pos, const glm::vec3& scale, const PhysicsBodyType type) {
    PhysicsBodyDesc body_desc {
      .position = pos,
      .type = type, 
      .mass = 1.0f, 
      .is_active = true
    };

    body = physics_world_add_body(body_desc);
    collider = BoxCollider{.half_size = scale / 2.0f};
    physics_body_add_collider(body, COLLIDER_BOX, &collider);

    mesh = mesh_create();
  }

  void update() {
    
  }

  void render(const glm::vec4& color) {
    render_mesh(body->transform, mesh, color);
  }
};

// App
/////////////////////////////////////////////////////////////////////////////////
struct App {
  Camera camera;
  Camera* current_cam;

  Entity player, platform;
  Font* font;
};

static App s_app;
/////////////////////////////////////////////////////////////////////////////////

static bool collision_callback(const EventType type, const EventDesc& desc) {
  if(type != EVENT_ENTITY_COLLISION) {
    return false;
  } 

  printf("COLLIDED\n");

  return true;
}

// Public functions
/////////////////////////////////////////////////////////////////////////////////
bool app_init(void* user_data) {
  // Loading the default font
  s_app.font = font_load("assets/font/bit5x3.ttf", 256.0f);
  renderer2d_set_default_font(s_app.font);

  // Disable the cursor
  input_cursor_show(true);
  
  // Camera init 
  s_app.camera = camera_create(glm::vec3(10.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, -3.0f));
  
  // Editor init
  editor_init(glm::vec3(10.0f, 5.0f, 10.0f), glm::vec3(0.0f, 1.0f, -3.0f), false);

  // This can be switched between the game camera and editor camera
  s_app.current_cam = &s_app.camera;

  // Physics init 
  physics_world_create(glm::vec3(0.0f, 0.0f, 0.0f));
 
  s_app.player.init(glm::vec3(10.0f, 0.0f, 10.0f), glm::vec3(1.0f), PHYSICS_BODY_DYNAMIC);
  s_app.platform.init(glm::vec3(10.0f, -10.0f, 10.0f), glm::vec3(50.0f, 0.1f, 50.0f), PHYSICS_BODY_STATIC); 

  event_listen(EVENT_ENTITY_COLLISION, collision_callback);

  return true;
}

void app_shutdown(void* user_data) {
  physics_world_destroy();
  editor_shutdown();
}

void app_update(void* user_data) {
  camera_update(s_app.current_cam);
  camera_move(s_app.current_cam);

  if(input_key_pressed(KEY_G)) {
    physics_world_set_gravity(glm::vec3(0.0f, 9.81f, 0.0f));
  }

  physics_world_update(gclock_delta_time());
  s_app.player.update();
}

void app_render(void* user_data) {
  renderer_clear(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
  editor_begin();

  renderer_begin(s_app.current_cam);
  s_app.player.render(glm::vec4(1.0f)); 
  s_app.platform.render(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)); 
  renderer_end();
  
  renderer2d_begin();
  renderer2d_end();
 
  editor_end();
  renderer_present();
}
/////////////////////////////////////////////////////////////////////////////////
