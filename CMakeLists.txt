cmake_minimum_required(VERSION 4.0.2)
project(waterengine)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(deps/glfw)

add_executable(waterengine src/main.cpp
        src/Input/input.h
        src/Input/input.cpp
        deps/glad/src/glad.c
        src/Backend/GLFW.cpp
        src/Backend/GLFW.h
        src/Renderer/renderer.h
        src/Renderer/renderer.cpp
        src/Renderer/ShaderProgram.h
        src/Renderer/ShaderProgram.cpp
        src/Renderer/vertex.h
        deps/stb/stb_image.h
        src/Renderer/Texture2D.h
        src/Renderer/Texture2D.cpp
        src/Models/Models.h
        src/World/Object.h
        src/World/World.h
        src/Models/Models.cpp)

target_include_directories(waterengine PUBLIC src deps/glfw/include deps/glad/include deps/glm deps/stb)
target_link_libraries(waterengine glfw ${GLFW_LIBRARIES})
set_target_properties(waterengine PROPERTIES DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}" WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
