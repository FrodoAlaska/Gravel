#include "resource_manager.h"
#include "resources/material.h"
#include "resources/mesh.h"
#include "resources/model.h"
#include "resources/texture.h"
#include "resources/font.h"
#include "math/vertex.h"
#include "defines.h"

#include <string>
#include <unordered_map>
#include <vector>

// ResourceManager
/////////////////////////////////////////////////////////////////////////////////
struct ResourceManager {
  std::string res_path; 

  std::unordered_map<std::string, Texture*> textures;
  std::unordered_map<std::string, Font*> fonts;
  std::unordered_map<std::string, Mesh*> meshes;
  std::unordered_map<std::string, Material*> materials;
  std::unordered_map<std::string, Model*> models;
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

Mesh* find_mesh(const std::string& id) {
  if(s_res_man.meshes.find(id) != s_res_man.meshes.end()) {
    return s_res_man.meshes[id];
  }

  return nullptr;
}

Material* find_material(const std::string& id) {
  if(s_res_man.materials.find(id) != s_res_man.materials.end()) {
    return s_res_man.materials[id];
  }

  return nullptr;
}

Model* find_model(const std::string& id) {
  if(s_res_man.models.find(id) != s_res_man.models.end()) {
    return s_res_man.models[id];
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
  
  for(auto& [key, value] : s_res_man.meshes) {
    mesh_destroy(value);
  }
  s_res_man.meshes.clear();
  
  for(auto& [key, value] : s_res_man.materials) {
    material_unload(value);
  }
  s_res_man.materials.clear();
}

Texture* resources_add_texture(const std::string& id, const std::string& path) {
  std::string full_path = s_res_man.res_path + path; 
  
  s_res_man.textures[id] = texture_load(full_path);
  return s_res_man.textures[id];
}

Texture* resources_add_texture(const std::string& id, i32 width, i32 height, TextureFormat format, void* pixels) {
  s_res_man.textures[id] = texture_load(width, height, format, pixels);
  return s_res_man.textures[id];
}

Font* resources_add_font(const std::string& path, const std::string& id) {
  std::string full_path = s_res_man.res_path + path; 
  
  s_res_man.fonts[id] = font_load(full_path, 256.0f);
  return s_res_man.fonts[id];
}

Mesh* resources_add_mesh(const std::string& id) {
  s_res_man.meshes[id] = mesh_create();
  return s_res_man.meshes[id];
}

Mesh* resources_add_mesh(const std::string& id, const std::vector<Vertex3D>& vertices, const std::vector<u32>& indices) {
  s_res_man.meshes[id] = mesh_create(vertices, indices);
  return s_res_man.meshes[id];
}

Material* resources_add_material(const std::string& id, 
                                 Texture* diffuse, 
                                 Texture* specular, 
                                 const std::string& shader_path) {
  s_res_man.materials[id] = material_load(diffuse, specular, shader_path);
  return s_res_man.materials[id];
}

Model* resources_add_model(const std::string& id, const std::string& path) {
  std::string full_path = s_res_man.res_path + path; 

  s_res_man.models[id] = model_load(path);
  return s_res_man.models[id];
}

Texture* resources_get_texture(const std::string& id) {
  return find_texture(id);
}

Font* resources_get_font(const std::string& id) {
  return find_font(id);
}

Mesh* resources_get_mesh(const std::string& id) {
  return find_mesh(id);
}

Material* resources_get_material(const std::string& id) {
  return find_material(id);
}

Model* resources_get_model(const std::string& id) {
  return find_model(id);
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
    font_unload(font);
    s_res_man.fonts.erase(id);
    
    return true;
  }

  return false;
}

bool resources_remove_mesh(const std::string& id) {
  Mesh* mesh = find_mesh(id);
  if(mesh) {
    mesh_destroy(mesh);
    s_res_man.fonts.erase(id);
    
    return true;
  }

  return false;
}

bool resources_remove_material(const std::string& id) {
  Material* material = find_material(id);
  if(material) {
    material_unload(material);
    s_res_man.materials.erase(id);
    
    return true;
  }

  return false;
}

bool resources_remove_model(const std::string& id) {
  Model* model = find_model(id);
  if(model) {
    model_unload(model);
    s_res_man.models.erase(id);
    
    return true;
  }

  return false;
}
/////////////////////////////////////////////////////////////////////////////////
