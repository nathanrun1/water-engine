cmake_minimum_required(VERSION 4.1)
project(waterengine)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(deps/glfw)

add_executable(waterengine src/main.cpp
        include/input.h
        src/input.cpp
        deps/glad/src/glad.c)

target_include_directories(waterengine PUBLIC include deps/glfw/include deps/glad/include)
target_link_libraries(waterengine glfw ${GLFW_LIBRARIES})
