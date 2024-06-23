#include "collider.h"
#include "physics/collision_data.h"
#include "physics/physics_body.h"

#include <glm/glm.hpp>

#include <limits>

// Private functions
/////////////////////////////////////////////////////////////////////////////////
static const glm::vec2 get_aabb_interval(const Collider* collider, const glm::vec3& axis) {
  glm::vec2 result = glm::vec3(0.0f);
 
  result.x = glm::dot(collider->points[0], axis);
  result.y = result.x;

  for(u32 i = 1; i < POINTS_MAX; i++) {
    f32 proj = glm::dot(collider->points[i], axis);

    if(proj < result.x) {
      result.x = proj;
    }
    if(proj > result.y) {
      result.y = proj;
    }
  }

  return result;
}

static bool check_axis_overlap(CollisionData* data, const Collider* coll1, const Collider* coll2, const glm::vec3& axis) {
  glm::vec2 interval1 = get_aabb_interval(coll1, axis);
  glm::vec2 interval2 = get_aabb_interval(coll2, axis);

  // No overlap therefore no collision
  if((interval1.x >= interval2.y) || (interval2.x >= interval1.y)) {
    return false;
  }

  f32 depth = glm::min(interval2.y - interval1.x, interval1.y - interval2.x);
  if(depth < data->depth) {
    data->depth   = depth; 
    data->normal  = axis;
  }

  return true;
}

static const glm::vec3 get_arth_mean(const i32 count, const glm::vec3* vertices) {
  glm::vec3 sum = glm::vec3(0.0f);

  for(u32 i = 0; i < count; i++) {
    sum.x += vertices[i].x;
    sum.y += vertices[i].y;
    sum.z += vertices[i].z;
  }

  return sum / (f32)count;
}
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
const bool collider_is_colliding(const Collider* coll1, const Collider* coll2, CollisionData* data) {
  data->coll1         = (Collider*)coll1; // Remove the const because fuck you
  data->coll2         = (Collider*)coll2;
  data->depth         = std::numeric_limits<f32>().max();
  data->normal        = glm::vec3(0.0f);

  // All of the axes to check overlaping on
  glm::vec3 axes[] = {
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 1.0f),
  };

  // Check if there's overlaping on all the 3 axeses
  for(u32 i = 0; i < 3; i++) {
    if(!check_axis_overlap(data, coll1, coll2, axes[i])) {
      return false;
    }
  }

  // Getting the direction of the two center points
  glm::vec3 dir = coll2->body->position - coll1->body->position;

  // if(glm::dot(dir, data->normal) < 0.0f) {
  //   data->normal = -data->normal;
  // }

  return true;
}

void collider_update_points(Collider* collider, const glm::vec3& pos) {
  // MIN = Left most side 
  // MAX = Right most side
  //
  // \5------------------------6\
  //  \                        | \
  //  |\1----------------------|--\2                      
  //  | |                      |   |
  //  | |                      |   | 
  //  | |                      |   | 
  //  | |                      |   | 
  //  | |                      |   | 
  //  | |                      |   | 
  //  8-|----------------------7\  |
  //  \ |                        \ |
  //   \4-------------------------\3

  collider->min = pos - (collider->scale / 2.0f);
  collider->max = pos + (collider->scale / 2.0f);

  collider->points[0] = collider->min;                                                // Point 1 
  collider->points[1] = glm::vec3(collider->max.x, collider->min.y, collider->min.z); // Point 2
  collider->points[2] = glm::vec3(collider->max.x, collider->max.y, collider->min.z); // Point 3
  collider->points[3] = glm::vec3(collider->min.x, collider->max.y, collider->min.z); // Point 4 

  collider->points[4] = glm::vec3(collider->min.x, collider->min.y, collider->max.z); // Point 5
  collider->points[5] = glm::vec3(collider->max.x, collider->min.y, collider->max.z); // Point 6
  collider->points[6] = collider->max;                                                // Point 7
  collider->points[7] = glm::vec3(collider->min.x, collider->max.y, collider->max.z); // Point 8
}
/////////////////////////////////////////////////////////////////////////////////
