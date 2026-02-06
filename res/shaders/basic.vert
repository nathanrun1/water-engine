#version 460

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 texCoord;

uniform mat4 u_model;
uniform mat4 u_VP;

void main() {
    gl_Position = u_VP * u_model * vec4(aPos, 1.0);
    texCoord = aTexCoord;
}
