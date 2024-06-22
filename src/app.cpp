#include "app.h"
#include "core/clock.h"
#include "core/input.h"
#include "core/event.h"
#include "graphics/renderer.h"
#include "graphics/renderer2d.h"
#include "graphics/camera.h"
#include "math/transform.h"
#include "physics/physics_body.h"
#include "physics/physics_world.h"
#include "resources/material.h"
#include "resources/mesh.h"
#include "utils/utils.h"

#include <glm/glm.hpp>

#include <cstdio>
#include <string>

struct Entity {
  Transform transform; 
  Material* material;
  Mesh* mesh; 
  PhysicsBody* body;

  static bool callback(const EventType type, const EventDesc& desc) {
    static i32 num = 0;

    if(type != EVENT_ENTITY_COLLISION) {
      return false;
    }

    num++;
    printf("COLLISION - %i: %s - %s\n", num, desc.coll_data.coll1->id.c_str(), desc.coll_data.coll2->id.c_str());

    return true;
  }

  void init(const glm::vec3& pos, bool dynamic, const std::string& id) {
    mesh = mesh_create();
    material = material_load_default();
    transform_create(&transform, pos);

    body = physics_world_add_body(pos, dynamic, this);
    physics_body_add_collider(body, transform.scale, id);

    event_listen(EVENT_ENTITY_COLLISION, callback);
  }

  void move() {
    if(input_key_down(KEY_A)) {
      body->velocity.z = -10.0f;
    } 
    else if(input_key_down(KEY_D)) {
      body->velocity.z = 10.0f;
    } 
    else {
      body->velocity.z = 0.0f;
    }
    
    if(input_key_down(KEY_W)) {
      body->velocity.x = 10.0f;
    } 
    else if(input_key_down(KEY_S)) {
      body->velocity.x = -10.0f;
    } 
    else {
      body->velocity.x = 0.0f;
    }

    transform_translate(&transform, body->velocity * (f32)gclock_delta_time());
  }

  void render() {
    render_mesh(transform, mesh, material);
  }
};

// App
/////////////////////////////////////////////////////////////////////////////////
struct App {
  Camera camera;
  Entity player, enemy;
};

static App s_app;
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
bool app_init(void* user_data) {
  s_app.camera = camera_create(glm::vec3(10.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, -3.0f));
  input_cursor_show(true);

  physics_world_create(glm::vec3(0.0f, 0.0f, 0.0f));

  s_app.player.init(glm::vec3(10.0f, 0.0f, 10.0f), true, "player");
  s_app.enemy.init(glm::vec3(10.0f, 0.0f, 20.0f), false, "enemy");

  return true;
}

void app_shutdown(void* user_data) {
  physics_world_destroy();
}

void app_update(void* user_data) {
  if(input_key_pressed(KEY_ESCAPE)) {
    event_dispatch(EVENT_GAME_QUIT, EventDesc{});
  }

  camera_update(&s_app.camera);
  camera_move(&s_app.camera);

  physics_world_update(gclock_delta_time());

  s_app.player.move();
}

void app_render(void* user_data) {
  renderer_clear(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
  // editor_begin();

  renderer_begin(&s_app.camera);
  s_app.player.render();
  s_app.enemy.render();
  renderer_end();
  
  renderer2d_begin();
  renderer2d_end();
 
  // editor_end();
  renderer_present();
}
/////////////////////////////////////////////////////////////////////////////////
