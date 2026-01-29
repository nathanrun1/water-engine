#include <iostream>

#include "Renderer/renderer.h"
#include "Backend/glfw_backend.h"

int main() {
    GLFW::setWindowWidth(800);
    GLFW::setWindowWidth(600);
    GLFW::init();
    
    Renderer::init();
    
    while (!GLFW::windowShouldClose()) {
        Renderer::renderMain();
        GLFW::endFrame();
    }
    GLFW::destroy();
}