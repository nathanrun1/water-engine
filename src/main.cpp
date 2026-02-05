#include <iostream>

#include "Renderer/renderer.h"
#include "backend/glfw_backend.h"
#include "world/transform.h"

// TO IMPLEMENT:
// - Load from .obj
// X Geometry batching
//   - Vertex deduplication
// - Instancing

Vertex cubeVertices[] = {
    {{-0.5f, -0.5f, -0.5f,}, {0.0f, 0.0f}},
    {{ 0.5f, -0.5f, -0.5f,}, {1.0f, 0.0f,}},
    {{ 0.5f,  0.5f, -0.5f,}, {1.0f, 1.0f,}},
    {{ 0.5f,  0.5f, -0.5f,}, {1.0f, 1.0f,}},
    {{-0.5f,  0.5f, -0.5f,}, {0.0f, 1.0f,}},
    {{-0.5f, -0.5f, -0.5f,}, {0.0f, 0.0f,}},
    {{-0.5f, -0.5f,  0.5f,}, {0.0f, 0.0f,}},
    {{ 0.5f, -0.5f,  0.5f,}, {1.0f, 0.0f,}},
    {{ 0.5f,  0.5f,  0.5f,}, {1.0f, 1.0f,}},
    {{ 0.5f,  0.5f,  0.5f,}, {1.0f, 1.0f,}},
    {{-0.5f,  0.5f,  0.5f,}, {0.0f, 1.0f,}},
    {{-0.5f, -0.5f,  0.5f,}, {0.0f, 0.0f,}},
    {{-0.5f,  0.5f,  0.5f,}, {1.0f, 0.0f,}},
    {{-0.5f,  0.5f, -0.5f,}, {1.0f, 1.0f,}},
    {{-0.5f, -0.5f, -0.5f,}, {0.0f, 1.0f,}},
    {{-0.5f, -0.5f, -0.5f,}, {0.0f, 1.0f,}},
    {{-0.5f, -0.5f,  0.5f,}, {0.0f, 0.0f,}},
    {{-0.5f,  0.5f,  0.5f,}, {1.0f, 0.0f,}},
    {{ 0.5f,  0.5f,  0.5f,}, {1.0f, 0.0f,}},
    {{ 0.5f,  0.5f, -0.5f,}, {1.0f, 1.0f,}},
    {{ 0.5f, -0.5f, -0.5f,}, {0.0f, 1.0f,}},
    {{ 0.5f, -0.5f, -0.5f,}, {0.0f, 1.0f,}},
    {{ 0.5f, -0.5f,  0.5f,}, {0.0f, 0.0f,}},
    {{ 0.5f,  0.5f,  0.5f,}, {1.0f, 0.0f,}},
    {{-0.5f, -0.5f, -0.5f,}, {0.0f, 1.0f,}},
    {{ 0.5f, -0.5f, -0.5f,}, {1.0f, 1.0f,}},
    {{ 0.5f, -0.5f,  0.5f,}, {1.0f, 0.0f,}},
    {{ 0.5f, -0.5f,  0.5f,}, {1.0f, 0.0f,}},
    {{-0.5f, -0.5f,  0.5f,}, {0.0f, 0.0f,}},
    {{-0.5f, -0.5f, -0.5f,}, {0.0f, 1.0f,}},
    {{-0.5f,  0.5f, -0.5f,}, {0.0f, 1.0f,}},
    {{ 0.5f,  0.5f, -0.5f,}, {1.0f, 1.0f,}},
    {{ 0.5f,  0.5f,  0.5f,}, {1.0f, 0.0f,}},
    {{ 0.5f,  0.5f,  0.5f,}, {1.0f, 0.0f,}},
    {{-0.5f,  0.5f,  0.5f,}, {0.0f, 0.0f,}},
    {{-0.5f,  0.5f, -0.5f},  { 0.0f, 1.0f}}
};

unsigned int cubeIndices[] = {
     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35
};

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

int main() {
    GLFW::setWindowWidth(800);
    GLFW::setWindowWidth(600);
    GLFW::init();

    std::vector<Vertex> vertices(std::begin(cubeVertices), std::end(cubeVertices));
    std::vector<unsigned int> indices(std::begin(cubeIndices), std::end(cubeIndices));
    Assets::Model cube = Assets::createModel(vertices, indices);
    
    Renderer::init();
    
    while (!GLFW::windowShouldClose()) {
        Renderer::begin_draw();
        for (glm::vec3& pos : cubePositions) {
            Transform transform;
            transform.position = pos;
            transform.set_euler_angles(0.0f, glfwGetTime() * glm::radians(90.0f), 0.0f);
            Renderer::draw_model_with_transform(cube, transform);
        }
        GLFW::endFrame();
    }
    GLFW::destroy();
}