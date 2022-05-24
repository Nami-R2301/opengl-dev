cmake_minimum_required(VERSION 3.16)
project(opengl-dev)

set(CMAKE_CXX_STANDARD 11)

find_package(glfw3 REQUIRED)
find_package(OpenGL 4.5 REQUIRED)
find_package(X11 REQUIRED)

add_executable(opengl-dev src/engine.cpp "src/OpenGL Graphics/window.cpp" "src/OpenGL Graphics/vertex.cpp"
        "src/OpenGL Graphics/shader.cpp" "src/OpenGL Graphics/color.cpp" "src/Game logic/game.cpp"
        "src/Game logic/time.cpp" "tests/vertex_test.cpp" "src/Math/vector_2f.cpp" "src/Math/vector_3f.cpp"
        "src/Math/matrix_4f.cpp" "src/Math/quaternion.cpp" "src/OpenGL Graphics/render.cpp"
        "src/OpenGL Graphics/mesh.cpp" src/Logs/logger.cpp Include/Logs/logger.h "src/Game logic/input.cpp" "Include/Game logic/input.h" src/Math/transform.cpp Include/Math/transform.h "Include/OpenGL Graphics/res_loader.h" "src/OpenGL Graphics/res_loader.cpp")

target_link_libraries(opengl-dev PUBLIC glfw cunit OpenGL::GL ${CMAKE_DL_LIBS})
