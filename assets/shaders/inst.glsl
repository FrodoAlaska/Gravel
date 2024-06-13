@type vertex
#version 460 core 

// Layouts
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in mat4 aModel;

// Uniform block
layout(std140, binding = 0) uniform matrices 
{
  mat4 u_view_projection;
};

void main() 
{
  gl_Position = u_view_projection * aModel * vec4(aPos, 1.0f);
}

@type fragment 
#version 460 core 

// Outputs 
out vec4 frag_color;

// Uniforms 
uniform vec4 u_color;

void main() 
{
  frag_color = u_color;
}
