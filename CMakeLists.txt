cmake_minimum_required(VERSION 4.0.2)
project(waterengine)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(deps/glfw)

add_executable(waterengine src/main.cpp
        src/backend/glfw_input.h
        src/backend/glfw_input.cpp
        deps/glad/src/glad.c
        src/Backend/glfw_backend.cpp
        src/Backend/glfw_backend.h
        src/renderer/Renderer.h
        src/renderer/Renderer.cpp
        src/renderer/shader_program.h
        src/renderer/shader_program.cpp
        src/renderer/Vertex.h
        deps/stb/stb_image.h
        src/renderer/Texture2D.h
        src/renderer/Texture2D.cpp
        src/assets/meshes.h
        src/world/Object.h
        src/world/World.h
        src/assets/meshes.cpp
        src/world/Transform.h
        src/world/Transform.cpp
        src/Math/Quaternion.h
        src/world/camera/camera.h)

target_include_directories(waterengine PUBLIC src deps/glfw/include deps/glad/include deps/glm deps/stb deps/spdlog/include)
target_link_libraries(waterengine glfw ${GLFW_LIBRARIES})
set_target_properties(waterengine PROPERTIES DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}" WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
