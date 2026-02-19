#version 460

// Light type enum values
#define LTYPE_POINT 0
#define LTYPE_DIRECTIONAL 1
#define LTYPE_AMBIENT 2

#define MATERIAL_UNLIT 1

#define MAX_LIGHTS 8

#define PI 3.1415926535897932384626433832795
const float EPS = 0.0001;

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

    uint flags;
} uMaterial;

layout (binding = 0) uniform sampler2DArray uMaterialMapArray;

uniform vec3 uCameraPos;


in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

out vec4 fragColor;

vec3 get_albedo() {
    return texture(uMaterialMapArray, vec3(texCoord, uMaterial.albedoId)).rgb * uMaterial.albedoScale;
}

// TRGGX NDF
//   Represents density of microfacets with normals within halfway-aligned solid angle per solid angle size per unit macrosurface area.
//   Retrieved from: https://learnopengl.com/PBR/Theory#:~:text=GGX%20for%20G.-,Normal%20distribution%20function,-The%20normal%20distribution
float D_GGXTR(float roughness, float NdotH) {
    float a = roughness * roughness;
    float a2 = a * a;
    float denom = NdotH * NdotH;
    denom = denom * (a2 - 1) + 1;
    denom = denom * denom * PI;
    
    return a2 / EPS, denom;
}

// Schlick GGX Geometry function
//   Represents the portion of un-occluded microfacets. Accounts for shadowing (blocked from light) and
//   masking (blocked from view).
//   Retrieved from: https://learnopengl.com/PBR/Theory#:~:text=return%20nom%20/%20denom%3B%0A%7D-,Geometry%20function,-The%20geometry%20function
float G_SchlickGGX(float NdotD, float k) {
    return NdotD / (NdotD * (1.0 - k) + k);
}
float G_Smith(float roughness, float NdotV, float NdotL) {
    float k = roughness + 1.0;
    k = (k * k) / 8.0;
    return G_SchlickGGX(NdotV, k) * G_SchlickGGX(NdotL, k);
}

// Fresnel Schlick approximation
//   Represents specular reflectivity. That is, the portion of incoming light that is reflected, as opposed to refracted.
//   Retrieved from: https://learnopengl.com/PBR/Theory#:~:text=return%20ggx1%20*%20ggx2%3B%0A%7D-,Fresnel%20equation,-The%20Fresnel%20equation
vec3 F_Schlick(vec3 half_dir, vec3 view_dir, vec3 albedo, float metallic) {
    vec3 F_0 = vec3(0.04);
    F_0 = mix(F_0, albedo, metallic);
    float HdotV = max(EPS, dot(half_dir, view_dir));
    float grazing = HdotV * HdotV;
    grazing = grazing * grazing;
    grazing = HdotV * grazing;
    grazing = 1 - grazing;
    return grazing * (vec3(1.0) - F_0) + F_0;
}

vec3 radiance(Light light) {
    vec3 albedo = get_albedo();

    if (light.type == LTYPE_AMBIENT) {
        return light.intensity * light.color * albedo;
    }
    
    // TODO: calculate normal with normal map, tangent space
    vec3 view_dir = normalize(uCameraPos - fragPos);
    vec3 light_dir = light.type == LTYPE_DIRECTIONAL ? light.position : light.position - fragPos;
    light_dir = normalize(light_dir);
    vec3 irradiance = light.intensity * light.color;
    float metallic = texture(uMaterialMapArray, vec3(texCoord, uMaterial.metallicId)).r * uMaterial.metallicScale;
    
    // Cook-Torrance specular
    // Retrieved from: https://learnopengl.com/PBR/Theory#:~:text=Cook%2DTorrance%20specular%20BRDF
    vec3 half_dir = normalize(light_dir + view_dir);
    float roughness = texture(uMaterialMapArray, vec3(texCoord, uMaterial.roughnessId)).r * uMaterial.roughnessScale;
    float NdotL = max(EPS, dot(normal, light_dir));
    float NdotV = max(EPS, dot(normal, view_dir));
    float NdotH = max(EPS, dot(normal, half_dir));

    float D = D_GGXTR(roughness, NdotH);
    vec3 F = F_Schlick(half_dir, view_dir, albedo, metallic);
    float G = G_Smith(roughness, NdotV, NdotL);
    vec3 nom = D * G * F;
    float denom = 4 * NdotV * NdotL;
    vec3 specular = nom / denom;
    
    vec3 diffuse = ((1 - metallic) * (1 - F)) / PI;
    diffuse *= albedo;
    
    return NdotL * (diffuse + specular) * irradiance;
}

void main() {
    if ((uMaterial.flags & MATERIAL_UNLIT) > 0) {
        fragColor = vec4(get_albedo(), 0.0);
        return;
    }

    vec3 total_irradiance = vec3(0.0);
    for (uint i = 0; i < num_lights; ++i) {
        total_irradiance += radiance(lights[i]);
    }
    fragColor = vec4(total_irradiance, 1.0);
}