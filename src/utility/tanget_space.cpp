#include "tangent_space.h"

#include <unordered_map>
#include <glm/vec3.hpp>

/** Calculates the tangent vector for a given triangle, defined by three vertices */
glm::vec3 _calculate_tangent(const Vertex& v1, const Vertex& v2, const Vertex& v3) {
    glm::vec3 edge1 = v1.position - v2.position;
    glm::vec3 edge2 = v1.position - v3.position;
    glm::vec2 delta_uv1 = v1.texCoord - v2.texCoord;
    glm::vec2 delta_uv2 = v1.texCoord - v3.texCoord;
    
    glm::mat2 delta_uv(delta_uv1, delta_uv2);
    glm::mat3x2 edges = glm::transpose(glm::mat2x3(edge1, edge2));
    
    // [E1, E2]^T = [DUV1, DUV2]^T * [T, B]^T
    // -> [T, B]^T = [DUV1, DUV2]^T^-1 * [E1, E2]^T -> we return the first column of the result, i.e. T
    // Based on assumption that [T, B] is basis of tangent space (basically texture coordinate space) in world space. 
    // That is, [T, B] transforms from tangent space to world space.
    return glm::normalize(glm::transpose(glm::inverse(delta_uv) * edges)[0]);
}

/** 
 * Updates the vertex's tangent based on total amount of tangents calculated and most newly calculated tangent. 
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
    for (int i = 0; i < indices.size() / 3; i += 3) {
        glm::vec3 tangent = _calculate_tangent(
            vertices[indices[i]],
            vertices[indices[i+1]],
            vertices[indices[i+2]]
        );
        for (int j = i; j < i + 3; ++j) {
            Vertex& v = vertices[indices[j]];
            unsigned int num_tangents = ++tangents_calculated[indices[j]];
            _update_tangent(v, num_tangents, tangent);
        }
    }
}
