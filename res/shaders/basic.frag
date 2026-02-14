#version 460

// Light type enum values
#define LTYPE_POINT 0
#define LTYPE_DIRECTIONAL 1

#define MAX_LIGHTS 8

struct Light {
    vec3 position;
    uint type;
    vec3 color;
    float intensity;
};

in vec2 texCoord;
in vec3 normal;

out vec4 fragColor;

layout (binding = 0) uniform sampler2DArray uAlbedoArray;
uniform uint uMaterial;
layout (std140) uniform LightBlock {
    uint num_lights;
    Light lights[MAX_LIGHTS];
};

void main() {
    //fragColor = vec4(mix(vec2(0.0), vec2(1.0), texCoord), 0.5, 1.0);
    fragColor = texture(uAlbedoArray, vec3(texCoord, uMaterial));
}