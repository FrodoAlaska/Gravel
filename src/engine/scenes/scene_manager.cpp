#include "scene_manager.h"
#include "scenes/scene.h"

#include <cstdio>
#include <unordered_map>
#include <string>

// SceneManager
/////////////////////////////////////////////////////////////////////////////////
struct SceneManager {
  std::unordered_map<std::string, Scene*> scenes;
  Scene* current_scene;
};

static SceneManager* s_scn_man;
/////////////////////////////////////////////////////////////////////////////////

// Private functions
/////////////////////////////////////////////////////////////////////////////////
bool find_scene(const std::string& name) {
  return s_scn_man->scenes.find(name) != s_scn_man->scenes.end();
}
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
void scene_manager_init() {
  s_scn_man = new SceneManager{};
  s_scn_man->current_scene = nullptr;
}

void scene_maneger_shutdown() {
  if(!s_scn_man) {
    return;
  }

  for(auto& [key, value] : s_scn_man->scenes) {
    scene_destroy(value);
  }
  
  s_scn_man->scenes.clear();
  s_scn_man->current_scene = nullptr; 

  delete s_scn_man;
}

void scene_manager_update() {
  if(!s_scn_man->current_scene) {
    return;
  }
  
  scene_update(s_scn_man->current_scene);
}

void scene_manager_render() {
  if(!s_scn_man->current_scene) {
    return;
  }

  scene_render(s_scn_man->current_scene); 
}

Scene* scene_manager_add_scene(const SceneDesc& desc) {
  // Scene already exists. So just return that   
  if(find_scene(desc.scene_name)) {
    return s_scn_man->scenes[desc.scene_name];
  }

  // Add a new scene
  s_scn_man->scenes[desc.scene_name] = scene_create(desc);
  return s_scn_man->scenes[desc.scene_name];
}

void scene_manager_load_scene(const std::string& scene_name) {
  // Can't find the scene name given in the map
  if(!find_scene(scene_name)) {
    fprintf(stderr, "[ERROR]: Could not find scene with name \'%s\'", scene_name.c_str());
    return; 
  }

  // Just load the scene otherwise
  s_scn_man->current_scene = s_scn_man->scenes[scene_name];
}

const Scene* scene_manager_get_current_scene() {
  return s_scn_man->current_scene;
}
/////////////////////////////////////////////////////////////////////////////////
