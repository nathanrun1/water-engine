#ifndef WATERENGINE_MESHES_H
#define WATERENGINE_MESHES_H
#include <vector>
#include <span>

#include "renderer/vertex.h"

namespace Assets {
    struct Mesh {
        const unsigned int id;
    };

    /* Creates the mesh from the given vertices and indices */
    const Mesh create_mesh(const std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);

    /* Retrieve a reference to the given mesh's vertices */
    std::span<const Vertex> get_mesh_vertices(const Mesh& mesh);

    /* Retrieve a reference to the given mesh's vertex buffer indices */
    std::span<const unsigned int> get_mesh_indices(const Mesh& mesh);

    /* Retrieve a reference to the entire span of all mesh vertices */
    std::span<const Vertex> get_all_mesh_vertices();

    /* Retrieve a reference to the entire span of all mesh indices */
    std::span<const unsigned int> get_all_mesh_indices();
}

#endif //WATERENGINE_MESHES_H