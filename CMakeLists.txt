cmake_minimum_required(VERSION 3.21)
project(Game_openGL)

set(CMAKE_CXX_STANDARD 14)

add_executable(opengl main.cpp)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(opengl PUBLIC glfw OpenGL::GL ${CMAKE_DL_LIBS})

target_link_libraries(opengl PUBLIC glfw OpenGL::GL ${CMAKE_DL_LIBS})
