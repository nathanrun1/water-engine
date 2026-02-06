#include "meshes.h"

namespace Assets {
    /* References to range of vertex and index data of a mesh */
    struct MeshRange {
        /* The mesh's vertices */
        std::span<const Vertex> vertices;

        /* Indices referring to the mesh's vertices, in the desired draw order */
        std::span<const unsigned int> indices;
    };

    std::vector<Vertex> g_meshVertices;
    std::vector<unsigned int> g_meshIndices;
    std::unordered_map<unsigned int, MeshRange> g_meshRanges;

    const Mesh create_mesh(const std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
        const Mesh newMesh = Mesh(g_meshRanges.size());

        unsigned int vertexOffset = g_meshVertices.size();
        unsigned int indexOffset = g_meshIndices.size();
        
        g_meshVertices.insert(g_meshVertices.end(), vertices.begin(), vertices.end());
        g_meshIndices.insert(g_meshIndices.end(), indices.begin(), indices.end());

        std::span<const Vertex> fullVertexSpan(g_meshVertices);
        std::span<const unsigned int> fullIndexSpan(g_meshIndices);

        MeshRange newMeshRange(
            fullVertexSpan.subspan(vertexOffset, vertices.size()),
            fullIndexSpan.subspan(indexOffset, indices.size())
        );

        g_meshRanges[newMesh.id] = newMeshRange;
        return newMesh;
    }

    std::span<const Vertex> get_mesh_vertices(const Mesh &mesh) {
        return g_meshRanges[mesh.id].vertices;
    }

    std::span<const unsigned int> get_mesh_indices(const Mesh &mesh) {
        return g_meshRanges[mesh.id].indices;
    }

    std::span<const Vertex> get_all_mesh_vertices() {
        return std::span(g_meshVertices);
    }

    std::span<const unsigned int> get_all_mesh_indices() {
        return std::span(g_meshIndices);
    }
};