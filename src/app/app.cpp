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
#include "resources/mesh.h"

#include <glm/glm.hpp>

#include <string>

struct Entity {
  PhysicsBody* body;
  BoxCollider collider; 
  Mesh* mesh; 

  void init(glm::vec3 pos, glm::vec3 scale, PhysicsBodyType type, f32 mass) {
    PhysicsBodyDesc desc {
      .position = pos, 
      .type = type, 
      .user_data = this, 
      .mass = mass, 
      .restitution = 1.0f, 
      .is_active = true,
    };

    body = physics_world_add_body(desc);
    collider = BoxCollider{.half_size = scale / 2.0f};
    physics_body_add_collider(body, COLLIDER_BOX, &collider);

    mesh = mesh_create();
  }

  void render(glm::vec4 color) {
    render_mesh(body->transform, mesh, color);
  }
};

#define MAX_ENTITIES 2

// App
/////////////////////////////////////////////////////////////////////////////////
struct App {
  Camera camera;
  Camera* current_cam;

  Entity entities[MAX_ENTITIES];
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

  // Disable the cursor
  input_cursor_show(false);
  
  // Camera init 
  s_app.camera = camera_create(glm::vec3(10.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, -3.0f));
  
  // Editor init
  editor_init(glm::vec3(10.0f, 5.0f, 10.0f), glm::vec3(0.0f, 1.0f, -3.0f), false);

  // This can be switched between the game camera and editor camera
  s_app.current_cam = &s_app.camera;

  physics_world_set_gravity(glm::vec3(0.0f));

  s_app.entities[0].init(glm::vec3(10.0f, 0.0f, 10.0f), glm::vec3(1.0f), PHYSICS_BODY_DYNAMIC, 1.0f);
  s_app.entities[1].init(glm::vec3(10.0f, -5.0f, 10.0f), glm::vec3(50.0f, 0.1f, 50.0f), PHYSICS_BODY_STATIC, 0.0f);

  return true;
}

void app_shutdown(void* user_data) {
  editor_shutdown();
}

void app_update(void* user_data) {
  camera_update(s_app.current_cam);
  camera_move(s_app.current_cam);

  s_app.current_cam->position = s_app.entities[0].body->transform.position;

  if(input_key_pressed(KEY_G)) {
    physics_world_set_gravity(glm::vec3(0.0f, 9.81f, 0.0f));
  }

  if(input_key_pressed(KEY_SPACE)) {
    physics_body_apply_linear_force(s_app.entities[0].body, glm::vec3(0.0f, 10.0f, 0.0f));
  }
}

void app_render(void* user_data) {
  renderer_clear(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
  editor_begin();

  renderer_begin(s_app.current_cam);
  // s_app.entities[0].render(glm::vec4(1.0f));
  s_app.entities[1].render(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
  renderer_end();
  
  renderer2d_begin();
  renderer2d_end();
 
  editor_end();
  renderer_present();
}
/////////////////////////////////////////////////////////////////////////////////
