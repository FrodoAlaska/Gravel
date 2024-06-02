#include "font.h"
#include "defines.h"
#include "graphics/texture.h"

#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftmodapi.h>
#include <glad/gl.h>

#include <fstream>
#include <string>
#include <cstdio>

// Private functions
/////////////////////////////////////////////////////////////////////////////////
static u8* get_font_data(const std::string& path) {
  std::ifstream file(path, std::ifstream::binary);
  if(!file.is_open()) {
    fprintf(stderr, "[ERROR]: Failed to open font file \'%s\'\n", path.c_str());
    return nullptr;
  }

  file.seekg(0, file.end);
  usizei size = file.tellg();
  file.seekg(0, file.beg);

  u8* data = new u8[size]; 
  file.read((char*)data, size);

  return data; 
}

static void init_font_chars(Font* font, const f32 size) {
  for(u32 i = 0; i < font->glyphs_count; i++) {
    if(FT_Load_Char(font->face, i + 32, FT_LOAD_RENDER) != 0) {
      fprintf(stderr, "[ERROR]: Failed to load glyph \'%c\'\n", i);
      continue; 
    }

    font->glyphs[i].unicode = i + 32;
    font->glyphs[i].size = glm::ivec2(font->face->glyph->bitmap.width, font->face->glyph->bitmap.rows);
    font->glyphs[i].bearing = glm::ivec2(font->face->glyph->bitmap_left, font->face->glyph->bitmap_top);
    font->glyphs[i].advance_x = font->face->glyph->advance.x;
  
    if(font->face->glyph->bitmap.buffer) {
      font->glyphs[i].texture = texture_load(font->face->glyph->bitmap.width, 
                                             font->face->glyph->bitmap.rows, 
                                             GL_RED, 
                                             font->face->glyph->bitmap.buffer);
    }
    else {
      u8 pixels = 0x00;
      font->glyphs[i].texture = texture_load(font->face->glyph->bitmap.width, 
                                             font->face->glyph->bitmap.rows, 
                                             GL_RED, 
                                             &pixels);
    }
  }
}
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
Font* font_load(const std::string& path, const f32 size) {
  Font* font = new Font{};
 
  if(FT_Init_FreeType(&font->lib) != 0) {
    fprintf(stderr, "[ERROR]: Failed to initialize FreeType");
    return nullptr;
  }

  if(FT_New_Face(font->lib, path.c_str(), 0, &font->face)) {
    return nullptr; 
  }
  
  FT_Set_Pixel_Sizes(font->face, 0, size);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  
  font->glyphs_count = font->face->num_glyphs;
  font->glyphs = new Glyph[font->glyphs_count];

  // Go through each char and get the required values for rendering 
  init_font_chars(font, size);

  return font;
}

void font_unload(Font* font) {
  if(!font) {
    return;
  }

  for(u32 i = 0; i < font->glyphs_count; i++) {
    texture_unload(font->glyphs[i].texture);
  }
  
  FT_Done_Face(font->face);
  FT_Done_Library(font->lib);
  
  delete[] font->glyphs;
  delete font;
}

i32 font_get_glyph_index(const Font* font, i8 codepoint) {
  for(u32 i = 0; i < font->glyphs_count; i++) {
    if(font->glyphs[i].unicode == codepoint) {
      return i;
    }
  }
  
  return 0;
}
/////////////////////////////////////////////////////////////////////////////////
