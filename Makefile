OBJS = ./src/*.cpp ./src/physics/*.cpp

CC = g++ -std=c++20

INCLUDE_PATHS = -I./Libraries/glm -I./Libraries/glew/2.2.0_1/include -I/opt/homebrew/include

LIBRARY_PATHS =  -L./Libraries/glew/2.2.0_1/lib -L/opt/homebrew/lib

COMPILER_FLAGS = -w -Wdeprecated-volatile

LINKER_FLAGS = -framework OpenGL -framework Cocoa -framework IOKit -lglew -lassimp -lSDL2

OBJ_NAME = ./bin/main.exec 

build:
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
