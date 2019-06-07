GLUT_INCLUDES := -ID:\opt\freeglut\include
GLUT_LIBS := -lfreeglut_static -lopengl32 -lwinmm -lgdi32

GLEW_INCLUDES := -ID:\opt\glew-2.1.0\include
GLEW_LIBS := -LD:\opt\glew-2.1.0\lib\Release\x64 -lglew32

.PHONY:default clean run

default: game


game: main.o
	g++ -o game.exe main.o $(GLEW_LIBS) $(GLUT_LIBS) 

main.o: main.cc
	g++ -c main.cc -D FREEGLUT_STATIC $(GLUT_INCLUDES) $(GLEW_INCLUDES)

clean:
	rm -rf *.o game.exe

run:game
	./game.exe