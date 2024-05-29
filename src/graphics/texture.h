#pragma once

#include "defines.h"

#include <string>

// Public functions
/////////////////////////////////////////////////////////////////////////////////
struct Texture {
  u32 id;
  i32 width, height;
  i32 depth, slot, channels;
  u32 format;
};
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
Texture* texture_load(const std::string& path);
Texture* texture_load(i32 width, i32 height, u32 format, void* pixels);
void texture_unload(Texture* texture);
void texture_render(Texture* texture);
/////////////////////////////////////////////////////////////////////////////////
