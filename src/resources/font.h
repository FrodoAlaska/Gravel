#pragma once 

#include "defines.h"
#include "resources/texture.h"

#include <string>
#include <vector>

// Glyph
/////////////////////////////////////////////////////////////////////////////////
struct Glyph {
  i8 unicode;
  Texture* texture;

  i32 width, height;
  i32 x_offset, y_offset;
  
  i32 advance_x, kern, left_side_bearing;
  i32 left, right, top, bottom;
};
/////////////////////////////////////////////////////////////////////////////////

// Font
/////////////////////////////////////////////////////////////////////////////////
struct Font {
  f32 base_size;
  f32 ascent, descent, line_gap;
  f32 glyph_padding;

  std::vector<Glyph> glyphs;
  u32 glyphs_count;
};
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
Font* font_load(const std::string& path, const f32 size);
void font_unload(Font* font);
i32 font_get_glyph_index(const Font* font, i8 codepoint);
/////////////////////////////////////////////////////////////////////////////////
