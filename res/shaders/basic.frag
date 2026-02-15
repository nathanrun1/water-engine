#version 460

// Light type enum values
#define LTYPE_POINT 0
#define LTYPE_DIRECTIONAL 1
#define LTYPE_AMBIENT 2

#define MAX_LIGHTS 8

struct Light {
    vec3 position;
    vec3 color;
    uint type;
    float intensity;
};

layout (std140, binding = 0) uniform LightBlock {
    uint num_lights;
    Light lights[MAX_LIGHTS];
};

layout (std140, binding = 1) uniform Material {
    uint albedoId;
    uint roughnessId;
    uint metallicId;
    uint normalId;

    vec3 albedoScale;
    float roughnessScale;
    float metallicScale;
} uMaterial;

layout (binding = 0) uniform sampler2DArray uMaterialMapArray;

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

out vec4 fragColor;

void main() {
    vec3 total_irradiance = vec3(0.0);
    for (uint i = 0; i < num_lights; ++i) {
        Light light = lights[i];
        vec3 light_dir = light.type == LTYPE_DIRECTIONAL ? light.position : lights[i].position - fragPos;
        light_dir = normalize(light_dir);
        
        vec3 irradiance = light.color * light.intensity;
        irradiance *= light.type == LTYPE_AMBIENT ? 1.0f : dot(normal, light_dir);
        
        irradiance = dot(normal, normalize(lights[i].position - fragPos)) * light.intensity * light.color;
        total_irradiance += irradiance;
    }
    //fragColor = vec4(uMaterial.albedoScale, 1.0); // testing
    fragColor = vec4(total_irradiance, 1.0) * texture(uMaterialMapArray, vec3(texCoord, uMaterial.albedoId)) * vec4(uMaterial.albedoScale, 1.0);
}