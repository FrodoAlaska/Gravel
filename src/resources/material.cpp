#include "material.h"
#include "defines.h"
#include "graphics/color.h"
#include "graphics/shader.h"
#include "resources/texture.h"

#include <string>

// Public functions 
/////////////////////////////////////////////////////////////////////////////////
Material* material_load(Texture* diffuse, Texture* specular, const std::string& shader_path) {
  Material* mat = new Material{};
  mat->diffuse_map = diffuse;
  mat->specular_map = specular;
  mat->shader = shader_load(shader_path);
  mat->color = COLOR_WHITE;

  return mat;
}

Material* material_load_default(Shader* default_shader) {
  Material* mat = new Material{};
  
  u32 pixels = 0xffffffff;
  mat->diffuse_map = texture_load(1, 1, TEXTURE_FORMAT_RGBA, &pixels);
  mat->shader = default_shader;
  mat->color = COLOR_WHITE;

  return mat;
}

void material_unload(Material* mat) {
  texture_unload(mat->diffuse_map);
  texture_unload(mat->specular_map);

  // Do not unload the shader since the material does not own the pointer. 
  // It just points to it but does not own it.
  mat->shader = nullptr;

  delete mat;
}

void material_use(Material* mat) {
  // Use the shader 
  shader_bind(mat->shader);
  shader_upload_int(mat->shader, "u_diffuse", mat->diffuse_map->slot);
  // shader_upload_int(mat->shader, "u_specular", mat->specular_map->slot);

  // Use the maps (if they are valid/exist)
  if(mat->diffuse_map) {
    texture_use(mat->diffuse_map, mat->diffuse_map->slot);
  }

  if(mat->specular_map) {
    texture_use(mat->specular_map, mat->specular_map->slot);
  }
}

void material_set_color(Material* mat, const glm::vec4& color) {
  mat->color = color;
  shader_upload_vec4(mat->shader, "u_color", color);
}

void material_set_model(Material* mat, const glm::mat4& model) {
  shader_upload_mat4(mat->shader, "u_model", model);
}
/////////////////////////////////////////////////////////////////////////////////
