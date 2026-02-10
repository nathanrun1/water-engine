#include "meshes.h"

namespace Assets {
    /* References to range of vertex and index data of a mesh */
    struct MeshRange {
        /* The mesh's vertices */
        std::span<const Vertex> vertices;

        /* Indices referring to the mesh's vertices, in the desired draw order */
        std::span<const unsigned int> indices;
    };

    std::vector<Vertex> g_mesh_vertices;
    std::vector<unsigned int> g_mesh_indices;
    std::unordered_map<unsigned int, MeshRange> g_mesh_ranges;

    Mesh create_mesh(const std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
        const Mesh new_mesh = Mesh(g_mesh_ranges.size());

        unsigned int vertex_offset = g_mesh_vertices.size();
        unsigned int index_offset = g_mesh_indices.size();
        
        g_mesh_vertices.insert(g_mesh_vertices.end(), vertices.begin(), vertices.end());
        g_mesh_indices.insert(g_mesh_indices.end(), indices.begin(), indices.end());

        std::span<const Vertex> full_vertex_span(g_mesh_vertices);
        std::span<const unsigned int> full_index_span(g_mesh_indices);

        MeshRange new_mesh_range(
            full_vertex_span.subspan(vertex_offset, vertices.size()),
            full_index_span.subspan(index_offset, indices.size())
        );

        g_mesh_ranges[new_mesh.id] = new_mesh_range;
        return new_mesh;
    }

    std::span<const Vertex> get_mesh_vertices(const Mesh &mesh) {
        return g_mesh_ranges[mesh.id].vertices;
    }

    std::span<const unsigned int> get_mesh_indices(const Mesh &mesh) {
        return g_mesh_ranges[mesh.id].indices;
    }

    std::span<const Vertex> get_all_mesh_vertices() {
        return std::span(g_mesh_vertices);
    }

    std::span<const unsigned int> get_all_mesh_indices() {
        return std::span(g_mesh_indices);
    }
};