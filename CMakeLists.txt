cmake_minimum_required(VERSION 3.16)
project(opengl-dev)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(X11 REQUIRED)

add_executable(opengl-dev src/engine.cpp "Include/engine.h" src/window.cpp "src/OpenGL Graphics/vertex.cpp" "src/OpenGL Graphics/shader.cpp"
        "Include/OpenGL Graphics/shader.h" "src/OpenGL Graphics/vao.cpp" "src/OpenGL Graphics/color.cpp" "src/OpenGL Graphics/vbo.cpp"
        "src/OpenGL Graphics/evo.cpp" "src/OpenGL Graphics/constants.cpp" "src/Game logic/game.cpp" "Include/Game logic/game.h"
        "src/Game logic/game_time.cpp" "Include/Game logic/game_time.h" "Include/OpenGL Graphics/vertex_test.h"
        tests/vertex_test.cpp src/Math/vector_2f.cpp Include/Math/vector_2f.h src/Math/vector_3f.cpp Include/Math/vector_3f.h
        src/Math/matrix4f.cpp Include/Math/matrix4f.h src/Math/quaternion.cpp Include/Math/quaternion.h "src/OpenGL Graphics/render.cpp"
        "Include/OpenGL Graphics/render.h" "src/OpenGL Graphics/mesh.cpp" "Include/OpenGL Graphics/mesh.h")

target_link_libraries(opengl-dev PUBLIC glfw cunit OpenGL::GL ${CMAKE_DL_LIBS})
