cmake_minimum_required(VERSION 4.0.2)
project(waterengine)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(deps/glfw)

add_executable(waterengine src/main.cpp
        src/Input/input.h
        src/Input/input.cpp
        deps/glad/src/glad.c
        src/Backend/glfw_backend.cpp
        src/Backend/glfw_backend.h
        src/Renderer/renderer.h
        src/Renderer/renderer.cpp
        src/Renderer/shader.h
        src/Renderer/shader.cpp
        src/Renderer/vertex.h)

target_include_directories(waterengine PUBLIC src deps/glfw/include deps/glad/include deps/glm)
target_link_libraries(waterengine glfw ${GLFW_LIBRARIES})
set_target_properties(waterengine PROPERTIES DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}" WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
