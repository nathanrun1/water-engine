#version 460

in vec2 texCoord;
in vec3 normal;

out vec4 fragColor;

layout (binding = 0) uniform sampler2DArray uAlbedoArray;
uniform uint uMaterial;

void main() {
    //fragColor = vec4(mix(vec2(0.0), vec2(1.0), texCoord), 0.5, 1.0);
    fragColor = mix(texture(texture0, texCoord), texture(texture1, texCoord), 0.2);
}