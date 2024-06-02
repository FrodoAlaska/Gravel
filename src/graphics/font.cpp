#include "font.h"
#include "defines.h"
#include "graphics/texture.h"

#include <glad/gl.h>
#include <stb_truetype/stb_truetype.h>
#include <glm/glm.hpp>

#include <cstdio>
#include <string>
#include <fstream>

// Public functions
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

static void init_font_chars(Font* font, stbtt_fontinfo* info, const f32 size) {
  /*
   * NOTE: Bits and pieces of this code is borrowed from Raylib. Particularly, from 
   * the "rtext.c" file. Check them out if you have not already. 
   */

  // This will return a value that will get used constantly to put all the values 
  // that come out of the stb in "scaled" coordinates.  
  f32 scale_factor = stbtt_ScaleForPixelHeight(info, size);

  // Get the ascent, descent, and line gap of the font and put them in 
  // the scaled space 
  i32 ascent, descent, line_gap;
  stbtt_GetFontVMetrics(info, &ascent, &descent, &line_gap);

  font->ascent = ascent * scale_factor;
  font->descent = descent * scale_factor;

  for(u32 i = 0; i < font->glyphs_count; i++) { 
    Glyph* glyph = &font->glyphs[i];
    glyph->unicode = i + 32;

    // Getting the advance and the left side bearing of the specific codepoint/glyph.
    // The advance is the value required to "advance" to the next glyph
    stbtt_GetCodepointHMetrics(info, glyph->unicode, &glyph->advance_x, &glyph->left_side_bearing);
    glyph->advance_x *= scale_factor;

    // Getting the kern of the glyph. The kern is used to make some specific glyphs look better 
    // when next to each other.
    glyph->kern = stbtt_GetCodepointKernAdvance(info, glyph->unicode, font->glyphs[i + 1].unicode); 
    
    // Pixels of the specific codepoint, offset, and size 
    u8* bitmap = stbtt_GetCodepointBitmap(info, 
                                          scale_factor,
                                          scale_factor, 
                                          glyph->unicode, 
                                          &glyph->size.x, 
                                          &glyph->size.y, 
                                          &glyph->offset.x, 
                                          &glyph->offset.y);
   
    // Only give OpenGL the pixels when it is valid 
    if(bitmap) {
      glyph->texture = texture_load(glyph->size.x, glyph->size.y, GL_RED, bitmap);
    }  

    glyph->offset.y += font->ascent;
  }
}
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
Font* font_load(const std::string& path, const f32 size) {
  Font* font = new Font{};

  u8* data = get_font_data(path);

  stbtt_fontinfo info;
  if(stbtt_InitFont(&info, data, stbtt_GetFontOffsetForIndex(data, 0)) == 0) {
    fprintf(stderr, "[ERROR]: Failed to initialize stb for font \'%s\'\n", path.c_str());
    return font;
  }

  font->glyphs_count = info.numGlyphs;
  font->glyphs = new Glyph[font->glyphs_count];

  // Load the textures and required values for every glyph in the font 
  init_font_chars(font, &info, size);

  delete[] data;
  return font;
}

void font_unload(Font* font) {
  if(!font) {
    return;
  }

  for(u32 i = 0; i < font->glyphs_count; i++) {
    texture_unload(font->glyphs[i].texture);
  }
  
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
