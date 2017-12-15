CPPFLAGS=-c -std=c++11 -Wall -I /usr/local/include/ -I ./Box2D
LDLIBS=-o hill-racing -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -L ./Box2D/Build/Box2D -lBox2D

all: game

game: main.o
	g++ main.o $(LDLIBS)

main.o: main.cpp
	g++ main.cpp $(CPPFLAGS)
clean:
	rm *.o
