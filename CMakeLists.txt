cmake_minimum_required(VERSION 3.16)
project(opengl-dev)

set(CMAKE_CXX_STANDARD 11)

find_package(glfw3 REQUIRED)
find_package(OpenGL 4.5 REQUIRED)
find_package(X11 REQUIRED)

add_executable(opengl-dev src/Engine/engine.cpp "src/OpenGL Graphics/window.cpp" "src/OpenGL Graphics/vertex.cpp"
        "src/OpenGL Graphics/shader.cpp" "src/OpenGL Graphics/color.cpp" "src/Game logic/game.cpp"
        "src/Game logic/game_time.cpp" "tests/vertex_test.cpp" "src/Math/vector_2f.cpp" "src/Math/vector_3f.cpp"
        "src/Math/matrix_4f.cpp" "src/Math/quaternion.cpp" "src/OpenGL Graphics/renderer.cpp"
        "src/OpenGL Graphics/mesh.cpp" src/Logs/logger.cpp src/Logs/logger.h "src/Game logic/input.cpp" "src/Game logic/input.h" src/Math/transform.cpp src/Math/transform.h "src/OpenGL Graphics/res_loader.h" "src/OpenGL Graphics/res_loader.cpp" src/Math/camera.cpp src/Math/camera.h "src/OpenGL Graphics/texture.cpp" "src/OpenGL Graphics/texture.h" "src/Vendor/Stb/stdb_image.h" "src/OpenGL Graphics/material.cpp" "src/OpenGL Graphics/material.h" src/app.cpp "src/OpenGL Graphics/vertex_buffer.cpp" "src/OpenGL Graphics/vertex_buffer.h" "src/OpenGL Graphics/vertex_array_buffer.cpp" "src/OpenGL Graphics/vertex_array_buffer.h" "src/OpenGL Graphics/index_buffer.cpp" "src/OpenGL Graphics/index_buffer.h" "src/OpenGL Graphics/buffer_layout.h")

target_link_libraries(opengl-dev PUBLIC glfw cunit OpenGL::GL ${CMAKE_DL_LIBS})
