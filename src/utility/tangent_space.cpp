#include <iostream>

#include "tangent_space.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtx/io.hpp>

struct TangentBasis {
    glm::vec3 tangent;
    glm::vec3 bitangent;
};

/** Calculates tangent space basis for the given triangle defined by three vertices */
glm::mat2x3 _tangent_basis(const Vertex& v1, const Vertex& v2, const Vertex& v3) {
    glm::vec3 edge1 = v1.position - v2.position;
    glm::vec3 edge2 = v1.position - v3.position;
    glm::vec2 delta_uv1 = v1.tex_coord - v2.tex_coord;
    glm::vec2 delta_uv2 = v1.tex_coord - v3.tex_coord;
    
    glm::mat2 delta_uv(delta_uv1, delta_uv2);
    glm::mat2x3 edges(edge1, edge2);
    
    // [E1, E2]^T = [DUV1, DUV2]^T * [T, B]^T
    // -> [T, B]^T = [DUV1, DUV2]^T^-1 * [E1, E2]^T
    // That is, [T, B] transforms from tangent space to world space.
    return glm::transpose(edges * glm::inverse(delta_uv));
}

/** 
 * Updates the vertex's tangent (and invert_bitangent attribute) based on total amount of tangents calculated and most newly calculated tangent.
 * 
 * @details accounts for shared vertices between triangles, interpolating the tangent calculations from each one.
 */
void _update_tangent(Vertex& v, unsigned int num_tangents, const glm::vec3& tangent) {
    if (num_tangents == 1) {
        v.tangent = tangent;
        return;
    }
    v.tangent = glm::normalize(static_cast<float>(num_tangents) * v.tangent + tangent);
}

void calculate_tangents(const std::span<Vertex>& vertices, const std::span<unsigned int>& indices) {
    // map index to how many tangents calculated per
    // if >0, then do incremental average for that vertex's tangent
    std::unordered_map<unsigned int, size_t> tangents_calculated{};
    for (int i = 0; i < indices.size(); i += 3) {
        glm::vec3 tangent = _tangent_basis(
            vertices[indices[i]],
            vertices[indices[i+1]],
            vertices[indices[i+2]]
        )[0];
        for (int j = i; j < i + 3; ++j) {
            Vertex& v = vertices[indices[j]];
            unsigned int num_tangents = ++tangents_calculated[indices[j]];
            _update_tangent(v, num_tangents, tangent);
        }
    }
}
