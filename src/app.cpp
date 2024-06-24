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
#include "resources/font.h"
#include "resources/mesh.h"
#include "editor/editor.h"
#include "utils/utils_file.h"

#include <glm/glm.hpp>

#include <string>

struct Entity {
  Transform transform; 
  Mesh* mesh; 
  PhysicsBody* body;

  static bool callback(const EventType type, const EventDesc& desc) {
    if(type != EVENT_ENTITY_COLLISION) {
      return false;
    }

    return true;
  }

  void init(const glm::vec3& pos, bool dynamic, const std::string& id) {
    mesh = mesh_create();
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

    transform.position = body->position;
    transform_translate(&transform, glm::vec3(0.0f));
  }

  void render() {
    render_mesh(transform, mesh);
  }
};

// App
/////////////////////////////////////////////////////////////////////////////////
struct App {
  Camera camera;
  Camera* current_cam;

  Entity player, enemy;
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

  physics_world_create(glm::vec3(0.0f, 0.0f, 0.0f));

  s_app.player.init(glm::vec3(10.0f, 0.0f, 10.0f), true, "player");
  s_app.enemy.init(glm::vec3(10.0f, 0.0f, 20.0f), false, "enemy");

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

  s_app.player.move();
}

void app_render(void* user_data) {
  renderer_clear(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
  editor_begin();

  renderer_begin(s_app.current_cam);
  s_app.player.render();
  s_app.enemy.render();
  renderer_end();
  
  renderer2d_begin();
  render_text(30.0f, "SHADERS! YEAH!", glm::vec2(400.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
  renderer2d_end();
 
  editor_end();
  renderer_present();
}
/////////////////////////////////////////////////////////////////////////////////
