cmake_minimum_required(VERSION 3.16)
project(opengl-dev)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(X11 REQUIRED)

add_executable(opengl-dev src/main.cpp src/window.cpp src/vertex.cpp src/shader.cpp src/program.cpp
        src/vao.cpp src/color.cpp src/vbo.cpp src/evo.cpp src/constants.cpp Include/draw.h src/draw.cpp)

target_link_libraries(opengl-dev PUBLIC glfw cunit OpenGL::GL ${CMAKE_DL_LIBS})
