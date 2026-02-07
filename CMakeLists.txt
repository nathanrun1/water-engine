cmake_minimum_required(VERSION 4.0.2)
project(waterengine)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(deps/glfw)

add_executable(waterengine
        deps/glad/src/glad.c
        deps/stb/stb_image.h

        src/main.cpp
        src/backend/glfw_input.h
        src/backend/glfw_input.cpp
        src/backend/glfw_backend.cpp
        src/backend/glfw_backend.h
        src/Renderer/Renderer.h
        src/Renderer/Renderer.cpp
        src/renderer/shader_program.h
        src/renderer/shader_program.cpp
        src/Renderer/Vertex.h
        src/Renderer/Texture2D.h
        src/Renderer/Texture2D.cpp
        src/assets/meshes.h
        src/World/Object.h
        src/World/World.h
        src/assets/meshes.cpp
        src/World/Transform.h
        src/World/Transform.cpp
        src/world/camera/camera.h
        src/world/camera/camera.cpp
        src/assets/meshes.cpp
        src/assets/meshes.cpp
        src/world/camera/camera.cpp)

target_include_directories(waterengine PUBLIC src deps/glfw/include deps/glad/include deps/glm deps/stb deps/spdlog/include)
target_link_libraries(waterengine glfw ${GLFW_LIBRARIES})
set_target_properties(waterengine PROPERTIES DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}" WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
