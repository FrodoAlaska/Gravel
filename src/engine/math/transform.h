#pragma once

#include "defines.h"

#include <glm/glm.hpp>

// Transform
/////////////////////////////////////////////////////////////////////////////////
struct Transform {
  glm::vec3 position, rotation, scale;
  glm::mat4 transform;
};
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
void transform_create(Transform* transform, 
                      const glm::vec3& pos, 
                      const glm::vec3& rot = glm::vec3(1.0f), 
                      const glm::vec3& scale = glm::vec3(1.0f));
void transform_translate(Transform* transform, const glm::vec3& pos);
void transform_rotate(Transform* transform, const f32 rotation, const glm::vec3& axis);
void transform_scale(Transform* transform, const glm::vec3& scale);
/////////////////////////////////////////////////////////////////////////////////
