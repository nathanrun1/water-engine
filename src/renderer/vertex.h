#ifndef WATERENGINE_VERTEX_H
#define WATERENGINE_VERTEX_H

#include "glm/glm.hpp"
#include "glad/glad.h"

struct VertexAttributeDesc {
    unsigned int index;
    unsigned int size;
    unsigned int type;
    std::size_t offset;
};

struct Vertex {
    glm::vec3 position;
    glm::vec2 tex_coord;
    glm::vec3 normal;
    glm::vec3 tangent;
    bool invert_bitangent;

    static constexpr VertexAttributeDesc layout[] = {
        {0, 3, GL_FLOAT, 0},
        {1, 2, GL_FLOAT, sizeof(position)},
        {2, 3, GL_FLOAT, sizeof(position) + sizeof(tex_coord)},
        {3, 3, GL_FLOAT, sizeof(position) + sizeof(tex_coord) + sizeof(normal)},
        {4, 1, GL_FLOAT, sizeof(position) + sizeof(tex_coord) + sizeof(normal) + sizeof(tangent)}
    };
};

#endif //WATERENGINE_VERTEX_H