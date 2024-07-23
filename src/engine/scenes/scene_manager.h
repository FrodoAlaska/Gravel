#pragma once

#include "scenes/scene.h"

#include <unordered_map>
#include <string>

// Public functions
/////////////////////////////////////////////////////////////////////////////////
void scene_manager_init();
void scene_maneger_shutdown();
void scene_manager_update();
void scene_manager_render();

Scene* scene_manager_add_scene(const SceneDesc& desc);
void scene_manager_load_scene(const std::string& scene_name);
const Scene* scene_manager_get_current_scene();
/////////////////////////////////////////////////////////////////////////////////
