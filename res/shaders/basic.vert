#version 460

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec4 aTangent;

out vec2 fTexCoord;
out vec3 fNormal;
out vec4 fTangent;
out vec3 fPos;

uniform mat4 uModel;
uniform mat4 uVP;

void main() {
    gl_Position = uVP * uModel * vec4(aPos, 1.0);
    
    fTexCoord = aTexCoord;
    fNormal = normalize(mat3(transpose(inverse(uModel))) * aNormal);
    fTangent = aTangent;
    fPos = vec3(uModel * vec4(aPos, 1.0));
}
