#include "scene.h"
#include "scenes/object.h"
#include "scenes/player.h"
#include "ui/ui_canvas.h"

#include <vector>
#include <string>

// Public functions 
/////////////////////////////////////////////////////////////////////////////////
Scene* scene_create(const SceneDesc& desc) {
  Scene* scn = new Scene{};

  scn->player = desc.player;
  scn->objects = desc.objects;
  scn->canvases = desc.canvases;
  scn->scene_name = desc.scene_name;

  return scn;
}

void scene_destroy(Scene* scene) {
  if(!scene) {
    return;
  }
  
  player_destroy(scene->player);

  for(auto& obj : scene->objects) {
    object_destroy(obj);
  }
  scene->objects.clear();

  for(auto& canvas : scene->canvases) {
    ui_canvas_destroy(canvas);
  }
  scene->canvases.clear();

  delete scene;
}

void scene_update(Scene* scene) {
  player_update(scene->player);
}

void scene_render(Scene* scene) {
  player_render(scene->player);

  for(auto& obj : scene->objects) {
    object_render(obj);
  }

  for(auto& canvas : scene->canvases) {
    ui_canvas_render(canvas);
  }
}
/////////////////////////////////////////////////////////////////////////////////
