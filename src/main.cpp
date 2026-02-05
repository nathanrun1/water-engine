#include <iostream>

#include "Renderer/Renderer.h"
#include "Backend/GLFW.h"

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

int main() {
    GLFW::setWindowWidth(800);
    GLFW::setWindowWidth(600);
    GLFW::init();

    std::vector<Vertex> vertices(std::begin(cubeVertices), std::end(cubeVertices));
    std::vector<unsigned int> indices(std::begin(cubeIndices), std::end(cubeIndices));
    Assets::Model cube = Assets::createModel(vertices, indices);
    
    Renderer::init();
    
    while (!GLFW::windowShouldClose()) {
        Renderer::drawModelAtPosition(cube, glm::vec3(0.0, 0.0, 0.0));
        GLFW::endFrame();
    }
    GLFW::destroy();
}