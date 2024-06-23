#include "engine.h"
#include "app_desc.h"

#include "core/clock.h"
#include "core/window.h"
#include "core/input.h"
#include "core/event.h"

#include "graphics/renderer.h"
#include "graphics/renderer2d.h"

#include "audio/audio_system.h"

#include "resources/resource_manager.h"

#include <cstdio>

// Callbacks
/////////////////////////////////////////////////////////////////////////////////
bool game_quit(const EventType type, const EventDesc& desc) {
  if(type != EVENT_GAME_QUIT) {
    return false;
  }

  window_set_close(true);
  return true;
}
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
void engine_init(const AppDesc& desc) {
  // Window init 
  if(!window_create(1280, 720, "Gravel")) {
    printf("[ERROR]: Window failed to be created\n");
    return;
  }

  // Input init
  input_init();

  // Resource manager init 
  resources_init("assets/");

  // Renderer 3D init
  if(!renderer_create()) {
    printf("[ERROR]: Renderer failed to be created\n");
    return;
  }

  // Renderer 2D init
  if(!renderer2d_create()) {
    printf("[ERROR]: Renderer2D failed to be created\n");
    return;
  }

  // Audio init
  if(!audio_system_init()) {
    printf("[ERROR]: Audio system failed to be initialized\n");
    return;
  }

  // Listening to events
  event_listen(EVENT_GAME_QUIT, game_quit);

  // User app init 
  if(!desc.init_func(desc.user_data)) {
    fprintf(stderr, "[ERROR]: Could not initialize app\n");
    return;
  }
}

void engine_shutdown(AppDesc& desc) {
  desc.shutdown_func(desc.user_data); 

  audio_system_shutdown();

  renderer2d_destroy();
  renderer_destroy();
  
  resources_shutdown();
  window_destroy();
}

void engine_run(AppDesc& desc) {
  while(!window_should_close()) {
    if(input_key_pressed(window_get_exit_key())) {
      event_dispatch(EVENT_GAME_QUIT, EventDesc{});
    }

    gclock_update();
    desc.update_func(desc.user_data);
    input_update();
   
    desc.render_func(desc.user_data);

    window_poll_events();
  }
}
/////////////////////////////////////////////////////////////////////////////////
