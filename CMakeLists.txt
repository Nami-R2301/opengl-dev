cmake_minimum_required(VERSION 3.21)
project(opengl-dev)

set(CMAKE_CXX_STANDARD 17)

add_executable(opengl-dev src/main.cpp src/window.cpp src/vertex.cpp src/shader.cpp src/program.cpp
        src/vao.cpp src/color.cpp src/vbo.cpp src/evo.cpp)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(opengl-dev PUBLIC glfw cunit OpenGL::GL ${CMAKE_DL_LIBS})

target_link_libraries(opengl-dev PUBLIC glfw cunit OpenGL::GL ${CMAKE_DL_LIBS})
