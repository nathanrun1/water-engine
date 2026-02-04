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

    static constexpr VertexAttributeDesc layout[] = {
        {0, 3, GL_FLOAT, 0},
        {1, 2, GL_FLOAT, sizeof(position)}
    };
};

#endif //WATERENGINE_VERTEX_H