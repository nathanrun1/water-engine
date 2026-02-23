#ifndef WATERENGINE_TANGENT_SPACE_H
#define WATERENGINE_TANGENT_SPACE_H
#include <span>

#include "renderer/vertex.h"

/**
 * Calculates and assigns tangent vectors for a given set of vertices and indices, assuming each group of three vertices forms
 * a triangle.
 * @details indices.size() must be divisible by 3, vertex data must already have initialized position, texture coordinates, and normal
 */
void calculate_tangents(const std::span<Vertex>& vertices, const std::span<unsigned int>& indices);

#endif //WATERENGINE_TANGENT_SPACE_H