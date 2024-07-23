#include "object.h"
#include "graphics/renderer.h"
#include "math/transform.h"
#include "physics/physics_body.h"
#include "physics/collider.h"
#include "physics/physics_world.h"
#include "resources/mesh.h"

// Public functions
/////////////////////////////////////////////////////////////////////////////////
Object* object_create(const glm::vec3& scale, const PhysicsBodyDesc desc, const bool active) {
  Object* obj = new Object{};
  obj->body = physics_world_add_body(desc);
  obj->collider = BoxCollider{.half_size = scale / 2.0f};
  physics_body_add_collider(obj->body, COLLIDER_BOX, &obj->collider);

  obj->mesh = mesh_create();
  obj->is_active = active;

  return obj;
}

void object_destroy(Object* obj) {
  // Why are you trying to delete a null object???
  if(!obj) {
    return;
  }

  mesh_destroy(obj->mesh);
  delete obj;
}

void object_render(Object* obj) {
  // Don't render an inactive object. 
  // This is better for performance
  if(!obj->is_active) {
    return;
  }

  render_mesh(obj->body->transform, obj->mesh, glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
}
/////////////////////////////////////////////////////////////////////////////////
