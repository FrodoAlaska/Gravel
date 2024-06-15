#pragma once

#include "graphics/camera.h"
#include "resources/material.h"
#include "resources/mesh.h"
#include "math/transform.h"
#include "resources/model.h"

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

void render_mesh(const Transform& transform, Mesh* mesh, Material* mat);
void render_cube(const glm::vec3& position, const glm::vec3& scale, const f32& rotation, const glm::vec4& color);
void render_cube(const glm::vec3& position, const glm::vec3& scale, const glm::vec4& color);
void render_model(Model* model);
/////////////////////////////////////////////////////////////////////////////////
