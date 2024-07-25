#include "app.h"
#include "core/input.h"
#include "engine/graphics/renderer.h"
#include "engine/graphics/renderer2d.h"
#include "engine/graphics/camera.h"
#include "engine/physics/physics_world.h"
#include "engine/resources/font.h"
#include "editor/editor.h"
#include "physics/physics_body.h"
#include "physics/ray.h"
#include "scenes/object.h"
#include "scenes/player.h"
#include "utils/utils.h"

#include <cstdio>
#include <glm/glm.hpp>

#include <string>

/*
 * An example Gravel application. 
 * The 'engine.cpp' file uses the function pointer of this application to 
 * initialize, update, render, and shutdown the application. 
 * The function pointers are implemented here. 
 *
 * In this example, the application is a static variable where all of the functions can 
 * access freely. This is done just for simplicity sake. However, it would be better to make the 
 * application the engine's responsibility to declare and keep around. You can pass around the application 
 * in the 'user_data' parametar of each function pointer. You will have to convert the 'void*' to your 
 * desired application structure. 
 */

// App
/////////////////////////////////////////////////////////////////////////////////
struct App {
  Camera camera;
  Camera* current_cam;

  Font* font;

  Player* player;
  Object* obj;
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
  s_app.camera = camera_create(glm::vec3(1.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, -3.0f));
  
  // Editor init
  editor_init(glm::vec3(10.0f, 5.0f, 10.0f), glm::vec3(0.0f, 1.0f, -3.0f), false);

  // This can be switched between the game camera and editor camera
  s_app.current_cam = &s_app.camera;

  // Setting the gravity of the world
  physics_world_set_gravity(glm::vec3(0.0f));

  s_app.player = player_create(glm::vec3(5.0f, 5.0f, 14.5f));
  s_app.obj = object_create(glm::vec3(1.0f), PhysicsBodyDesc{
    .position = glm::vec3(5.0f, 0.0f, 15.0f), 
    .type = PHYSICS_BODY_STATIC, 
    .user_data = nullptr, 
    .mass = 1.0f, 
    .restitution = 1.0f
  });

  return true;
}

void app_shutdown(void* user_data) {
  editor_shutdown();
}

static f32 force = 0.0f, rot = 0.0f;

void app_update(void* user_data) {
  camera_update(s_app.current_cam);
  camera_move(s_app.current_cam);
  
  if(input_key_pressed(KEY_G)) {
    physics_world_set_gravity(glm::vec3(0.0f, -9.81f, 0.0f));
  }

  player_update(s_app.player);

  if(input_key_down(KEY_SPACE)) {
    force += 10.0f;
  }
  
  if(input_key_down(KEY_Q)) {
    rot += 1.0f;
  }

  if(input_key_released(KEY_SPACE)) {
    Ray ray {
      .position = s_app.current_cam->position, 
      .direction = s_app.current_cam->direction
    };

    RayIntersection intersect = ray_intersect(&ray, &s_app.player->body->transform, &s_app.player->collider);
    if(intersect.has_intersected) {
      physics_body_apply_linear_force(s_app.player->body, -s_app.current_cam->direction * force);
    }
  }
}

void app_render(void* user_data) {
  renderer_clear(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
  editor_begin();

  renderer_begin(s_app.current_cam);
  player_render(s_app.player);
  object_render(s_app.obj);
  renderer_end();
  
  renderer2d_begin();
  renderer2d_end();
 
  editor_end();
  renderer_present();
}
/////////////////////////////////////////////////////////////////////////////////
