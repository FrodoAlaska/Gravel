#include "resource_manager.h"
#include "resources/texture.h"
#include "resources/font.h"
#include "defines.h"

#include <cstdio>
#include <string>
#include <unordered_map>

// ResourceManager
/////////////////////////////////////////////////////////////////////////////////
struct ResourceManager {
  std::string res_path; 

  std::unordered_map<std::string, Texture*> textures;
  std::unordered_map<std::string, Font*> fonts;
};

static ResourceManager s_res_man;
/////////////////////////////////////////////////////////////////////////////////

// Private functions
/////////////////////////////////////////////////////////////////////////////////
Texture* find_texture(const std::string& id) {
  if(s_res_man.textures.find(id) != s_res_man.textures.end()) {
    return s_res_man.textures[id];
  }

  return nullptr;
}

Font* find_font(const std::string& id) {
  if(s_res_man.fonts.find(id) != s_res_man.fonts.end()) {
    return s_res_man.fonts[id];
  }

  return nullptr;
}
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
void resources_init(const std::string res_path) {
  s_res_man.res_path = res_path;
}

void resources_shutdown() {
  for(auto& [key, value] : s_res_man.fonts) {
    font_unload(value);
  }
  s_res_man.fonts.clear();
  
  for(auto& [key, value] : s_res_man.textures) {
    texture_unload(value);
  }
  s_res_man.textures.clear();
}

Texture* resources_add_texture(const std::string& id, const std::string& path) {
  std::string full_path = s_res_man.res_path + path; 
  
  s_res_man.textures[id] = texture_load(full_path);
  return s_res_man.textures[id];
}

Texture* resources_add_texture(const std::string& id, i32 width, i32 height, u32 format, void* pixels) {
  s_res_man.textures[id] = texture_load(width, height, format, pixels);
  return s_res_man.textures[id];
}

Font* resources_add_font(const std::string& path, const std::string& id) {
  std::string full_path = s_res_man.res_path + path; 
  
  s_res_man.fonts[id] = font_load(full_path, 256.0f);
  return s_res_man.fonts[id];
}

Texture* resources_get_texture(const std::string& id) {
  return find_texture(id);
}

Font* resources_get_font(const std::string& id) {
  return find_font(id);
}

bool resources_remove_texture(const std::string& id) {
  Texture* texture = find_texture(id);
  if(texture) {
    // Make sure to unload the texture before removing it
    texture_unload(texture);
    s_res_man.textures.erase(id);
    
    return true;
  }

  return false;
}

bool resources_remove_font(const std::string& id) {
  Font* font = find_font(id);
  if(font) {
    // Make sure to unload the font before removing it
    font_unload(font);
    s_res_man.fonts.erase(id);
    
    return true;
  }

  return false;
}
/////////////////////////////////////////////////////////////////////////////////
