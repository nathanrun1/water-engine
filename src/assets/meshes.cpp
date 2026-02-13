#include "meshes.h"

namespace Assets {
    /* References to range of vertex and index data of a mesh */
    struct MeshRange {
        /* The mesh's vertices */
        // std::span<const Vertex> vertices;
        size_t vertex_offset;
        size_t vertex_count;
        
        size_t index_offset;
        size_t index_count;
        /* Indices referring to the mesh's vertices, in the desired draw order */
        // std::span<const unsigned int> indices;
    };

    std::vector<Vertex> g_mesh_vertices;
    std::vector<unsigned int> g_mesh_indices;
    std::unordered_map<unsigned int, MeshRange> g_mesh_ranges;

    Mesh create_mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) {
        const auto new_mesh = Mesh(g_mesh_ranges.size());

        const unsigned int vertex_offset = g_mesh_vertices.size();
        const unsigned int index_offset = g_mesh_indices.size();
        
        g_mesh_vertices.insert(g_mesh_vertices.end(), vertices.begin(), vertices.end());
        g_mesh_indices.insert(g_mesh_indices.end(), indices.begin(), indices.end());

        const MeshRange new_mesh_range{
            vertex_offset, vertices.size(),
            index_offset, indices.size()
        };

        g_mesh_ranges[new_mesh.id] = new_mesh_range;
        return new_mesh;
    }

    std::span<const Vertex> get_mesh_vertices(const Mesh &mesh) {
        const MeshRange& range = g_mesh_ranges.at(mesh.id);
        return std::span(
            g_mesh_vertices.begin() + range.vertex_offset, 
            g_mesh_vertices.begin() + range.vertex_offset + range.vertex_offset
        );
    }

    std::span<const unsigned int> get_mesh_indices(const Mesh &mesh) {
        const MeshRange& range = g_mesh_ranges.at(mesh.id);
        return std::span(
            g_mesh_indices.begin() + range.index_offset, 
            g_mesh_indices.begin() + range.index_offset + range.index_count
        );
    }

    std::span<const Vertex> get_all_mesh_vertices() {
        return std::span(g_mesh_vertices);
    }

    std::span<const unsigned int> get_all_mesh_indices() {
        return std::span(g_mesh_indices);
    }
};