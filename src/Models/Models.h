#ifndef WATERENGINE_MODEL_H
#define WATERENGINE_MODEL_H
#include <vector>
#include <span>

#include "Renderer/Vertex.h"

namespace Assets {
    struct Model {
        const unsigned int id;
    };

    /* Creates the model from the given vertices and indices */
    const Model createModel(const std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);

    /* Retrieve a reference to the given model's vertices */
    std::span<const Vertex> getModelVertices(const Model& model);

    /* Retrieve a reference to the given model's vertex buffer indices */
    std::span<const unsigned int> getModelIndices(const Model& model);

    /* Retrieve a reference to the entire span of all model vertices */
    std::span<const Vertex> getAllModelVertices();

    /* Retrieve a reference to the entire span of all model indices */
    std::span<const unsigned int> getAllModelIndices();
}

#endif //WATERENGINE_MODEL_H