#include "transform.h"
#include "defines.h"

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

// Private functions
/////////////////////////////////////////////////////////////////////////////////
static void update_transform(Transform* transform, f32 rot) {
  transform->transform = glm::translate(glm::mat4(1.0f), transform->position) * 
                         glm::rotate(glm::mat4(1.0f), rot, transform->rotation) * 
                         glm::scale(glm::mat4(1.0f), transform->scale);
}
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
void transform_create(Transform* transform, const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale) {
  transform->position = pos; 
  transform->rotation = rot; 
  transform->scale    = scale;

  transform->transform = glm::mat4(1.0f);
  update_transform(transform, 0.0f);
}

void transform_translate(Transform* transform, const glm::vec3& pos) {
  transform->position = pos; 
  update_transform(transform, 0.0f);
}

void transform_rotate(Transform* transform, const f32 rotation, const glm::vec3& axis) {
  transform->rotation = axis; 
  update_transform(transform, rotation);
}

void transform_scale(Transform* transform, const glm::vec3& scale) {
  transform->scale = scale; 
  update_transform(transform, 0.0f);
}
/////////////////////////////////////////////////////////////////////////////////
