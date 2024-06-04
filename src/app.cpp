#include "app.h"
#include "core/clock.h"
#include "core/window.h"
#include "core/event.h"
#include "core/input.h"

#include "graphics/camera.h"
#include "graphics/renderer.h"
#include "graphics/renderer2d.h"

#include "audio/audio_system.h"

#include "editor/editor.h"
#include "resources/resource_manager.h"

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include <cstdio>

static Camera camera;
static Font* font;

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
  // editor_begin();

  renderer_begin(&camera);
  renderer_end();

  renderer2d_begin();
  render_text(font, 0.2f, "0123 ,", glm::vec2(200.0f, 200.0f), glm::vec4(1.0f));
  renderer2d_end();
 
  // editor_end();
  renderer_present();
}
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
bool app_init() {
  // Systems/managers init  
  ///////////////////////////////////////////////// 
  // Window init 
  if(!window_create(1280, 720, "Gravel")) {
    printf("[ERROR]: Window failed to be created\n");
    return false;
  }

  // Input init
  input_init();

  // Resource manager init 
  resources_init("assets/");

  // Renderer 3D init
  if(!renderer_create()) {
    printf("[ERROR]: Renderer failed to be created\n");
    return false;
  }

  // Renderer 2D init
  if(!renderer2d_create()) {
    printf("[ERROR]: Renderer2D failed to be created\n");
    return false;
  }

  // Audio init
  if(!audio_system_init()) {
    printf("[ERROR]: Audio system failed to be initialized\n");
    return false;
  }

  // Editor init
  editor_init();
  ///////////////////////////////////////////////// 

  font = resources_add_font("font/bit5x3.ttf", "regular_font");
  camera = camera_create(glm::vec3(10.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, -3.0f));

  return true;
}

void app_shutdown() {
  editor_shutdown();
  audio_system_shutdown();

  renderer2d_destroy();
  renderer_destroy();
  
  resources_shutdown();
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
