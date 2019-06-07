CC := g++

OUT_DIR := build
OUT_NAME := game.exe


GLUT_INCLUDES := -ID:\opt\freeglut\include
GLUT_LIBS := -lfreeglut_static -lopengl32 -lwinmm -lgdi32

GLEW_INCLUDES := -ID:\opt\glew-2.1.0\include
GLEW_LIBS := -LD:\opt\glew-2.1.0\lib\Release\x64 -lglew32



.PHONY:default clean run init

default: init $(OUT_DIR)/$(OUT_NAME)


$(OUT_DIR)/$(OUT_NAME): $(OUT_DIR)/main.o
	$(CC) $< -o $(OUT_DIR)/$(OUT_NAME) $(GLEW_LIBS) $(GLUT_LIBS) 

$(OUT_DIR)/main.o: src/main.cc
	$(CC) $< -c -o $(OUT_DIR)/main.o -D FREEGLUT_STATIC $(GLUT_INCLUDES) $(GLEW_INCLUDES)

clean:
	rm -rf ./$(OUT_DIR)/*

run: default
	./$(OUT_DIR)/$(OUT_NAME)

init:
	cd $(OUT_DIR) || mkdir $(OUT_DIR)