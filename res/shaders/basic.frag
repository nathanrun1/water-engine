#version 460

// Light type enum values
#define LTYPE_POINT 0
#define LTYPE_DIRECTIONAL 1
#define LTYPE_AMBIENT 2

#define MAX_LIGHTS 8

struct Light {
    vec3 position;
    uint type;
    vec3 color;
    float intensity;
};

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

out vec4 fragColor;

layout (binding = 0) uniform sampler2DArray uAlbedoArray;
uniform uint uMaterial;
layout (std140, binding = 0) uniform LightBlock {
    uint num_lights;
    Light lights[MAX_LIGHTS];
};

void main() {
    vec3 total_irradiance = vec3(0.0);
    for (uint i = 0; i < num_lights; ++i) {
        Light light = lights[i];
        vec3 light_dir = light.type == LTYPE_DIRECTIONAL ? light.position : lights[i].position - fragPos;
        light_dir = normalize(light_dir);
        
        vec3 irradiance = light.color * light.intensity;
        irradiance *= light.type == LTYPE_AMBIENT ? 1.0f : dot(normal, light_dir);
        
        irradiance = dot(normal, normalize(lights[i].position - fragPos)) * light.color; // TODO: adding intensity breaks it
        total_irradiance += irradiance;
    }
    fragColor = vec4(total_irradiance, 1.0) * texture(uAlbedoArray, vec3(texCoord, uMaterial));
}