#include "renderer.h"
#include "core/window.h"
#include "defines.h"
#include "graphics/camera.h"
#include "graphics/shader.h"
#include "components/mesh.h"
#include "components/transform.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include <string>
#include <cstdio>
#include <vector>

// ShaderType
/////////////////////////////////////////////////////////////////////////////////
enum ShaderType {
  SHADER_CAMERA, 
  SHADER_INSTANCE,
  SHADERS_MAX = 2,
};
/////////////////////////////////////////////////////////////////////////////////

// Renderer
/////////////////////////////////////////////////////////////////////////////////
struct Renderer {
  Shader* shaders[SHADERS_MAX];
  Shader* current_shader;

  u32 ubo; // Uniform buffer
  u32 instance_count = 0;

  Mesh* cube_mesh = nullptr;
  std::vector<glm::mat4> transforms;
};

static Renderer renderer;
/////////////////////////////////////////////////////////////////////////////////

// Private functions
/////////////////////////////////////////////////////////////////////////////////
bool gl_init() {
  // Loading GLAD
  if(!gladLoadGL(glfwGetProcAddress)) {
    printf("[ERROR]: Failed to initialize GLAD\n");
    return false;
  }
  else {
    window_set_current_context();
  }

  // Setting the GL viewport size
  glm::vec2 win_size = window_get_size();
  glViewport(0, 0, win_size.x, win_size.y);
 
  // Setting options
  glEnable(GL_STENCIL_TEST);
  glEnable(GL_MULTISAMPLE); 
  
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL); // Need this to enable back to front rendering for 2D 

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  return true;
}
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
const bool renderer_create() {
  if(!gl_init()) {
    return false;
  }

  // Creating uniform buffer  
  glGenBuffers(1, &renderer.ubo);
  glBindBuffer(GL_UNIFORM_BUFFER, renderer.ubo);
  glBufferData(GL_UNIFORM_BUFFER, sizeof(f32) * 1024, nullptr, GL_DYNAMIC_DRAW);
  glBindBufferBase(GL_UNIFORM_BUFFER, 0, renderer.ubo);

  // Shaders loading
  renderer.shaders[SHADER_CAMERA] = shader_load("assets/shaders/camera.glsl");
  renderer.shaders[SHADER_INSTANCE] = shader_load("assets/shaders/inst.glsl");
  renderer.current_shader         = renderer.shaders[SHADER_INSTANCE];

  // Creating the instance mesh
  renderer.cube_mesh = mesh_create();
  
  // Cube Mesh model matrix layout 
  glBindVertexArray(renderer.cube_mesh->vao); 
  glBindBuffer(GL_ARRAY_BUFFER, renderer.cube_mesh->ibo);
  
  // 1st colomn
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(glm::mat4), 0);
  glVertexAttribDivisor(1, 1); // Enabling instancing for the mesh
  
  // 2nd colomn
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 4, GL_FLOAT, false, sizeof(glm::mat4), (void*)(sizeof(f32) * 4));
  glVertexAttribDivisor(2, 1);
  
  // 3rd colomn
  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 4, GL_FLOAT, false, sizeof(glm::mat4), (void*)(sizeof(f32) * 8));
  glVertexAttribDivisor(3, 1);
  
  // 4th colomn
  glEnableVertexAttribArray(4);
  glVertexAttribPointer(4, 4, GL_FLOAT, false, sizeof(glm::mat4), (void*)(sizeof(f32) * 12));
  glVertexAttribDivisor(4, 1);

  return true;
}

void renderer_destroy() {
  renderer.transforms.clear();
  mesh_destroy(renderer.cube_mesh);

  for(u32 i = 0; i < SHADERS_MAX; i++) {
    shader_unload(renderer.shaders[i]);
  }
}

void renderer_clear(const glm::vec4& color) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(color.r, color.g, color.b, color.a);
}

void renderer_begin(const Camera* cam) {
  // Upload the view projection matrices through the uniform buffer 
  glBindBuffer(GL_UNIFORM_BUFFER, renderer.ubo);
  glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(cam->view_projection));
  
  renderer.instance_count = 0; 
  renderer.transforms.clear();
}

void renderer_end() {
  shader_bind(renderer.shaders[SHADER_INSTANCE]);

  // Upload the transform matrices to the instance buffer to be renderer 
  glBindBuffer(GL_ARRAY_BUFFER, renderer.cube_mesh->ibo); 
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::mat4) * renderer.transforms.size(), renderer.transforms.data());

  // Render all of the instances of the mesh
  glBindVertexArray(renderer.cube_mesh->vao);
  glDrawElementsInstanced(GL_TRIANGLES, renderer.cube_mesh->index_count, GL_UNSIGNED_INT, 0, renderer.instance_count);
}

void renderer_present() {
  window_swap_buffers();
}

void render_mesh(const Transform& transform, Mesh* mesh) {
  shader_bind(renderer.shaders[SHADER_CAMERA]);
  shader_upload_mat4(renderer.shaders[SHADER_CAMERA], "u_model", transform.transform); 

  glBindVertexArray(mesh->vao);
  glDrawElements(GL_TRIANGLES, mesh->index_count, GL_UNSIGNED_INT, 0);
}

void render_cube(const glm::vec3& position, const glm::vec3& scale, const glm::vec4& color) {
  shader_upload_vec4(renderer.shaders[SHADER_INSTANCE], "u_color", color); // @TODO: This is potantially slow 

  glm::mat4 model(1.0f);
  model = glm::translate(model, position) * 
          glm::rotate(model, 0.0f, glm::vec3(1.0f)) *
          glm::scale(model, scale);
  
  renderer.instance_count++;
  renderer.transforms.push_back(model);
}
/////////////////////////////////////////////////////////////////////////////////
