#version 460

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec2 texCoord;
out vec3 normal;

uniform mat4 uModel;
uniform mat4 uVP;

void main() {
    gl_Position = uVP * uModel * vec4(aPos, 1.0);
    texCoord = aTexCoord;
    normal = aNormal;
}
