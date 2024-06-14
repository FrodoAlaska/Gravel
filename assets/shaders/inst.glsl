@type vertex
#version 460 core 

// Layouts
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in mat4 aModel;
// layout (location = 4) in vec4 aColor;

// Uniform block
layout(std140, binding = 0) uniform matrices 
{
  mat4 u_view_projection;
};

// Outputs 
out VS_OUT {
  vec3 normal; 
  vec2 texture_coords;
  vec4 color;
} vs_out;

void main() 
{
  gl_Position = u_view_projection * aModel * vec4(aPos, 1.0f);

  vs_out.normal = aNormal;
  vs_out.texture_coords = aTexCoords;
  // vs_out.color = aColor;
}

@type fragment 
#version 460 core 

// Inputs 
in VS_OUT {
  vec3 normal; 
  vec2 texture_coords;
  vec4 color;
} fs_in;

// Outputs 
out vec4 frag_color;

// Uniforms 
uniform vec4 u_color;

void main() 
{
  frag_color = vec4(1.0f);//fs_in.color;
}
