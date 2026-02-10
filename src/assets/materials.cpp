#include "materials.h"

#include <vector>

namespace Assets {
    std::vector<Texture2D> g_mat_albedos;


    Material create_material(const Texture2D& albedo) {
        Material mat(g_mat_albedos.size());

        if (g_mat_albedos[0].same_dimensions(albedo)) {
            throw material_error("Failed to create material " + std::to_string(mat.id) + ", albedo texture dimensions differ from others.");
        }
        g_mat_albedos.push_back(albedo);

        return mat;
    }

    std::span<const Texture2D> get_all_albedos() {
        return std::span(g_mat_albedos);
    }
}
