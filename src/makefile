CC=g++
CFLAGS=-c -std=c++11 -I ./Box2D

all: game

game: main.o
	g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -L ./Box2D/Build/Box2D -lBox2D
	
main.o: main.cpp
	g++ main.cpp
	
clean:
	rm *.o
