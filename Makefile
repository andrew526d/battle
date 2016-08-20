CXXFLAGS=-g -std=c++11

all: ship.o field.o const.o game.o main.o *.h
	g++ -o battle ship.o field.o const.o game.o main.o -std=c++11

test: ship.o field.o const.o game.o test.o *.h
	g++ -o test ship.o field.o const.o game.o test.o -std=c++11

main.o: main.cpp *.h
	g++ -c main.cpp -std=c++11
	
test.o: test.cpp *.h
	g++ -c test.cpp -std=c++11
	
ship.o: ship.cpp *.h
	g++ -c ship.cpp -std=c++11
	
field.o: field.cpp *.h
	g++ -c field.cpp -std=c++11
	
game.o: game.cpp *.h
	g++ -c game.cpp -std=c++11

const.o: const.cpp *.h
	g++ -c const.cpp -std=c++11

