CC := g++

OUT_DIR := build
OUT_NAME := game.exe


GLUT_INCLUDES := -ID:\opt\freeglut\include
GLUT_LIBS := -lfreeglut_static -lopengl32 -lwinmm -lgdi32

GLEW_INCLUDES := -ID:\opt\glew-2.1.0\include
GLEW_LIBS := -LD:\opt\glew-2.1.0\lib\Release\x64 -lglew32

INCLUDES := $(GLUT_INCLUDES) $(GLEW_INCLUDES) -Isrc/include


.PHONY:default clean run init

default: init $(OUT_DIR)/$(OUT_NAME)


$(OUT_DIR)/$(OUT_NAME): $(OUT_DIR)/main.o $(OUT_DIR)/shaderUtil.o $(OUT_DIR)/fileReader.o
	$(CC) $^ -o $(OUT_DIR)/$(OUT_NAME) $(GLEW_LIBS) $(GLUT_LIBS) 

$(OUT_DIR)/main.o: src/main.cc
	$(CC) $< -c -o $(OUT_DIR)/main.o -D FREEGLUT_STATIC $(INCLUDES)

$(OUT_DIR)/shaderUtil.o: src/shaderUtil.cc
	$(CC) $< -c -o $@ -Isrc/include $(INCLUDES)

$(OUT_DIR)/fileReader.o: src/fileReader.cc
	$(CC) $< -c -o $@ -Isrc/include $(INCLUDES)

clean:
	rm -rf ./$(OUT_DIR)/*

run: default
	./$(OUT_DIR)/$(OUT_NAME)

init:
	cd $(OUT_DIR) || mkdir $(OUT_DIR)