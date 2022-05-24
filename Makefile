SRC_ROOT_DIRECTORY = ./src/
GAME_LOGIC_DIR = ./src/Game\ logic/
LOGS_DIR = ./src/Logs/
MATH_DIR = ./src/Math/
OPENGL_GRAPHICS_DIR = ./src/OpenGL\ Graphics/
TEST_DIR = ./tests/
CFLAGS = -Wall -03 -std=c++11
LDFLAGS = -lm -lglfw3 -lX11 -lpthread -ldl -lGL

all: compile run

compile:
	g++ $(SRC_ROOT_DIRECTORY)engine.cpp $(GAME_LOGIC_DIR)game.cpp $(GAME_LOGIC_DIR)input.cpp \
	$(GAME_LOGIC_DIR)time.cpp $(LOGS_DIR)logger.cpp $(MATH_DIR)matrix_4f.cpp $(MATH_DIR)quaternion.cpp \
	$(MATH_DIR)transform.cpp $(MATH_DIR)vector_2f.cpp $(MATH_DIR)vector_3f.cpp $(OPENGL_GRAPHICS_DIR)color.cpp \
	$(OPENGL_GRAPHICS_DIR)mesh.cpp $(OPENGL_GRAPHICS_DIR)render.cpp $(OPENGL_GRAPHICS_DIR)res_loader.cpp \
	$(OPENGL_GRAPHICS_DIR)shader.cpp $(OPENGL_GRAPHICS_DIR)vertex.cpp $(OPENGL_GRAPHICS_DIR)window.cpp \
	$(TEST_DIR)vertex_test.cpp -o game.exe $(LDFLAGS) $(CXX_FLAGS)

run:
	chmod +x game.exe
	./game.exe