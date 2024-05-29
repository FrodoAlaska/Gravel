#pragma once

#include "graphics/texture.h"

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

// Public functions
/////////////////////////////////////////////////////////////////////////////////
const bool renderer2d_create();
void renderer2d_destroy();
void renderer2d_flush();
void renderer2d_begin();
void renderer2d_end();

void render_quad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
void render_quad(const glm::vec2& position, const glm::vec2& size, Texture* texture, const glm::vec4& tint = glm::vec4(1.0f));
/////////////////////////////////////////////////////////////////////////////////
