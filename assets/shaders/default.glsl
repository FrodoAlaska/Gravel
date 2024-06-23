@type vertex
#version 460 core 

// Layouts 
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTextureCoords;

// Uniform block
layout(std140, binding = 0) uniform matrices 
{
  mat4 u_view_projection;
};

// Outputs 
out VS_OUT {
  vec3 normal; 
  vec2 texture_coords;
} vs_out;

uniform mat4 u_model;

void main() 
{
  gl_Position = u_view_projection * u_model * vec4(aPos, 1.0f);

  vs_out.normal = aNormal;
  vs_out.texture_coords = aTextureCoords;
}

@type fragment
#version 460 core 

// Inputs 
in VS_OUT {
  vec3 normal; 
  vec2 texture_coords;
} fs_in;

// Outputs 
out vec4 frag_color;

// Uniforms 
uniform vec4 u_color;
uniform sampler2D u_diffuse, u_specular;

void main() 
{
  frag_color = texture(u_diffuse, fs_in.texture_coords) * u_color;
}
