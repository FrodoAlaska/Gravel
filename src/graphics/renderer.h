#pragma once

#include "graphics/camera.h"
#include "components/mesh.h"
#include "components/transform.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

// Public functions
/////////////////////////////////////////////////////////////////////////////////
const bool renderer_create();
void renderer_destroy();
void renderer_clear(const glm::vec4& color);
void renderer_begin(const Camera* cam);
void renderer_end();
void renderer_present();

void render_mesh(const Transform& transform, Mesh* mesh);
void render_cube(const glm::vec3& position, const glm::vec3& scale, const glm::vec4& color);
/////////////////////////////////////////////////////////////////////////////////
