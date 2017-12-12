CC=g++
CFLAGS=-c -std=c++11 -Wall -I /usr/local/include/ -I ./Box2D

all: game

game: main.o
	g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -L ./Box2D/Build/Box2D -lBox2D
	
main.o: main.cpp
	g++ $(CFLAGS) main.cpp
	
clean:
	rm *.o
