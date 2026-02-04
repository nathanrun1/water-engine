#include <iostream>

#include "Renderer/Renderer.h"
#include "Backend/GLFW.h"

// TO IMPLEMENT:
// - Load from .obj
// X Geometry batching
//   - Vertex deduplication
// - Instancing

Vertex cubeVertices[] = {
    {{-0.5f, -0.5f, -0.5f},  {0.0f, 0.0}},
    {{ 0.5f, -0.5f, -0.5f},  {1.0f, 0.0f}},
    {{ 0.5f,  0.5f, -0.5f},  {1.0f, 1.0f}},
    {{-0.5f,  0.5f, -0.5f},  {0.0f, 1.0f}},
    {{-0.5f, -0.5f,  0.5f},  {0.0f, 0.0f}},
    {{ 0.5f, -0.5f,  0.5f},  {1.0f, 0.0f}},
    {{ 0.5f,  0.5f,  0.5f},  {1.0f, 1.0f}},
    {{-0.5f,  0.5f,  0.5f},  {0.0f, 1.0f}},
    {{-0.5f,  0.5f,  0.5f},  {1.0f, 0.0f}},
    {{-0.5f,  0.5f, -0.5f},  {1.0f, 1.0f}},
    {{-0.5f, -0.5f, -0.5f},  {0.0f, 1.0f}},
    {{ 0.5f,  0.5f,  0.5f},  {1.0f, 0.0f}},
    {{ 0.5f, -0.5f, -0.5f},  {0.0f, 1.0f}},
    {{ 0.5f, -0.5f,  0.5f},  {0.0f, 0.0f}},
    {{ 0.5f, -0.5f, -0.5f},  {1.0f, 1.0f}},
    {{-0.5f,  0.5f,  0.5f},  {0.0f, 0.0f}},
};

unsigned int cubeIndices[] = {
     0 ,1 ,2 ,2 ,3 ,0 ,
     4 ,5 ,6 ,6 ,7 ,4 ,
     8 ,9 ,10,10,4 ,8 ,
     11,2 ,12,12,13,11,
     10,14,5 ,5 ,4 ,10,
     3 ,2 ,11,11,15,3
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
        Renderer::drawModelAtPosition(cube, glm::vec3(0.0, 0.0, -3.0));
        GLFW::endFrame();
    }
    GLFW::destroy();
}