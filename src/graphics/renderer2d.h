#pragma once

#include "defines.h"

#include "resources/texture.h"
#include "resources/font.h"

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include <string>

// Rect
/////////////////////////////////////////////////////////////////////////////////
struct Rect {
  f32 x, y, width, height;
};
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
const bool renderer2d_create();
void renderer2d_destroy();
void renderer2d_flush();
void renderer2d_begin();
void renderer2d_end();

void render_quad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
void render_texture(Texture* texture, const Rect& src, const Rect& dest, const glm::vec4& tint = glm::vec4(1.0f));
void render_texture(Texture* texture, const glm::vec2& position, const glm::vec2& size, const glm::vec4& tint = glm::vec4(1.0f));
void render_text(const Font* font, const f32 size, const std::string& text, const glm::vec2& position, const glm::vec4& color);
/////////////////////////////////////////////////////////////////////////////////
