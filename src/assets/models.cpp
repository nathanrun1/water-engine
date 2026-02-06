#include "models.h"

namespace Assets {
    /* References to range of vertex and index data of a model */
    struct ModelRange {
        /* The model's vertices */
        std::span<const Vertex> vertices;

        /* Indices referring to the model's vertices, in the desired draw order */
        std::span<const unsigned int> indices;
    };

    std::vector<Vertex> g_modelVertices;
    std::vector<unsigned int> g_modelIndices;
    std::unordered_map<unsigned int, ModelRange> g_modelRanges;

    const Model create_model(const std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
        const Model newModel = Model(g_modelRanges.size());

        unsigned int vertexOffset = g_modelVertices.size();
        unsigned int indexOffset = g_modelIndices.size();
        
        g_modelVertices.insert(g_modelVertices.end(), vertices.begin(), vertices.end());
        g_modelIndices.insert(g_modelIndices.end(), indices.begin(), indices.end());

        std::span<const Vertex> fullVertexSpan(g_modelVertices);
        std::span<const unsigned int> fullIndexSpan(g_modelIndices);

        ModelRange newModelRange(
            fullVertexSpan.subspan(vertexOffset, vertices.size()),
            fullIndexSpan.subspan(indexOffset, indices.size())
        );

        g_modelRanges[newModel.id] = newModelRange;
        return newModel;
    }

    std::span<const Vertex> get_model_vertices(const Model &model) {
        return g_modelRanges[model.id].vertices;
    }

    std::span<const unsigned int> get_model_indices(const Model &model) {
        return g_modelRanges[model.id].indices;
    }

    std::span<const Vertex> get_all_model_vertices() {
        return std::span(g_modelVertices);
    }

    std::span<const unsigned int> get_all_model_indices() {
        return std::span(g_modelIndices);
    }
};