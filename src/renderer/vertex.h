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
    glm::vec2 texCoord;
    glm::vec3 normal;
    glm::vec3 tangent;

    static constexpr VertexAttributeDesc layout[] = {
        {0, 3, GL_FLOAT, 0},
        {1, 2, GL_FLOAT, sizeof(position)},
        {2, 3, GL_FLOAT, sizeof(position) + sizeof(texCoord)},
        {3, 3, GL_FLOAT, sizeof(position) + sizeof(texCoord) + sizeof(normal)}
    };
};

#endif //WATERENGINE_VERTEX_H