
#version 460 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec4 Color;
layout(location = 2) in vec2 TexCoords;

layout(set = 1, binding = 0) uniform Uniform {
  mat4 ModelViewProjectMatrix;
};

layout(location = 0) out vec4 VertexColor;
layout(location = 1) out vec2 VertexTexCoords;

void main() {
  gl_Position = ModelViewProjectMatrix * vec4(Position, 1.0f);
  VertexColor = Color;
  VertexTexCoords = TexCoords;
}

