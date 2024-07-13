#include "app.h"
#include "core/input.h"
#include "engine/core/clock.h"
#include "engine/graphics/renderer.h"
#include "engine/graphics/renderer2d.h"
#include "engine/graphics/camera.h"
#include "engine/physics/physics_world.h"
#include "engine/resources/font.h"
#include "editor/editor.h"
#include "physics/physics_body.h"
#include "resources/material.h"
#include "resources/mesh.h"

#include <glm/glm.hpp>

#include <string>

struct BoxCollider {
  glm::vec3 half_size;
  glm::vec3 min, max;
};

struct RayCollision {
  glm::vec3 collision_point;
  f32 distance;
  bool has_collided;
};

struct Ray {
  glm::vec3 position, direction;

  RayCollision intersect(const Transform* transform, BoxCollider& collider) {
    RayCollision ray;

    collider.min = transform->position - collider.half_size;
    collider.max = transform->position + collider.half_size;
    glm::vec3 tvals(-1.0f);

    for(u32 i = 0; i < 3; i++) {
      // Get the negative sides of the cube if the direction of the ray 
      // is positive
      if(direction[i] > 0) {
        tvals[i] = (collider.min[i] - position[i]) / direction[i]; 
      }
      // The positive sides of the cube 
      else if(direction[i] < 0) {
        tvals[i] = (collider.max[i] - position[i]) / direction[i];
      }
    }

    f32 best_t;

    // Try to get the max value
    if(tvals.x > tvals.y && tvals.x > tvals.z) {
      best_t = tvals.x;
    } 
    else if(tvals.y > tvals.x && tvals.y > tvals.z) {
      best_t = tvals.y;
    }
    else if(tvals.z > tvals.x && tvals.z > tvals.y) {
      best_t = tvals.z;
    }

    if(best_t < 0.0f) {
      ray.has_collided = false;
      return ray;
    }

    float epsilon = 0.0001f;
    glm::vec3 intersection = position + (direction * best_t);
    for(u32 i = 0; i < 3; i++) {
      // The best intersection that was found doesn't even touch the box!!!
      if((intersection[i] + epsilon) < collider.min[i] || intersection[i] > collider.max[i]) {
        ray.has_collided = false;
        return ray;
      }
    }

    ray.collision_point = intersection;
    ray.distance = best_t;
    ray.has_collided = true;
    return ray;
  } 
};

struct Player {
  BoxCollider collider; 
  PhysicsBody* body;
  Mesh* mesh;
  Material* material; 

  void init(const glm::vec3& pos) {
    body = physics_world_add_body(pos, true, this);
    collider = BoxCollider{.half_size = body->transform.scale / 2.0f};
    mesh = mesh_create();
    material = renderer_get_default_material();
  }

  void render() {
    render_mesh(body->transform, mesh, material);
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

  if(!input_key_pressed(KEY_SPACE)) {
    return;
  }

  Ray ray = {
    .position = s_app.current_cam->position,
    .direction = s_app.current_cam->direction,
  };

  RayCollision coll = ray.intersect(&s_app.player.body->transform, s_app.player.collider);
  if(coll.has_collided) {
    s_app.player.material->color = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
  }
  else {
    s_app.player.material->color = glm::vec4(1.0f);
  }
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
