#include "app.h"
#include "core/clock.h"
#include "core/window.h"
#include "core/event.h"
#include "core/input.h"
#include "graphics/camera.h"
#include "graphics/renderer.h"
#include "graphics/renderer2d.h"
#include "audio/audio_system.h"
#include "components/mesh.h"
#include "components/transform.h"
#include "editor/editor.h"

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include <cstdio>

static Mesh* mesh[10][10];
static Camera camera;
static Transform transforms[10][10];

// Private functions
/////////////////////////////////////////////////////////////////////////////////
static void update() {
  if(input_key_pressed(KEY_ESCAPE)) {
    window_set_close(true);
    event_dispatch(EVENT_GAME_QUIT, EventDesc{});
  }

  camera_update(&camera);
  camera_move(&camera);
}

static void render() {
  renderer_clear(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
  editor_begin();

  renderer_begin(&camera);
  for(u32 i = 0; i < 10; i++) {
    for(u32 j = 0; j < 10; j++) {
      render_cube(glm::vec3(j * 2.0f, 0.0f, i * 2.0f), glm::vec3(1.0f), glm::vec4(0, 1, 0, 1));
    }
  }
  
  // for(u32 i = 0; i < 10; i++) {
  //   for(u32 j = 0; j < 10; j++) {
  //     render_mesh(transforms[i][j], mesh[i][j]);
  //   }
  // }

  renderer_end();

  // renderer2d_begin();
  // render_quad(pos, glm::vec2(256.0f, 256.0f), glm::vec4(0, 0, 0, 1));
  // renderer2d_end();
 
  editor_end();
  renderer_present();
}
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
bool app_init() {
  // Systems/managers init  
  ///////////////////////////////////////////////// 
  if(!window_create(1280, 720, "Gravel")) {
    printf("[ERROR]: Window failed to be created\n");
    return false;
  }

  input_init();
  input_cursor_show(false);
  
  if(!renderer_create()) {
    printf("[ERROR]: Renderer failed to be created\n");
    return false;
  }
  
  if(!renderer2d_create()) {
    printf("[ERROR]: Renderer2D failed to be created\n");
    return false;
  }

  if(!audio_system_init()) {
    printf("[ERROR]: Audio system failed to be initialized\n");
    return false;
  }

  editor_init();
  ///////////////////////////////////////////////// 

  for(u32 i = 0; i < 10; i++) {
    for(u32 j = 0; j < 10; j++) {
      mesh[i][j] = mesh_create();
    }
  }
  
  for(u32 i = 0; i < 10; i++) {
    for(u32 j = 0; j < 10; j++) {
      transform_create(&transforms[i][j], glm::vec3(j * 2.0f, 0.0f, i * 2.0f));
    }
  }

  camera = camera_create(glm::vec3(10.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, -3.0f));

  return true;
}

void app_shutdown() {
  editor_shutdown();
  audio_system_shutdown();

  renderer2d_destroy();
  renderer_destroy();
  window_destroy();
}

void app_run() {
  while(!window_should_close()) {
    gclock_update();
    update();
    input_update();
   
    render();

    window_poll_events();
  }
}
/////////////////////////////////////////////////////////////////////////////////
