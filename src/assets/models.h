#ifndef WATERENGINE_MODEL_H
#define WATERENGINE_MODEL_H
#include <vector>
#include <span>

#include "Renderer/vertex.h"

namespace Assets {
    struct Model {
        const unsigned int id;
    };

    /* Creates the model from the given vertices and indices */
    const Model create_model(const std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);

    /* Retrieve a reference to the given model's vertices */
    std::span<const Vertex> get_model_vertices(const Model& model);

    /* Retrieve a reference to the given model's vertex buffer indices */
    std::span<const unsigned int> get_model_indices(const Model& model);

    /* Retrieve a reference to the entire span of all model vertices */
    std::span<const Vertex> get_all_model_vertices();

    /* Retrieve a reference to the entire span of all model indices */
    std::span<const unsigned int> get_all_model_indices();
}

#endif //WATERENGINE_MODEL_H