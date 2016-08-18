all: ship.o field.o main.o enumerator.o *.h
	g++ -o battle ship.o field.o enumerator.o main.o

test: ship.o field.o test.o enumerator.o *.h
	g++ -o test ship.o field.o test.o enumerator.o
	
main.o: main.cpp *.h
	g++ -c main.cpp
	
test.o: test.cpp *.h
	g++ -c test.cpp
	
ship.o: ship.cpp *.h
	g++ -c ship.cpp
	
field.o: field.cpp *.h
	g++ -c field.cpp 
	
enumerator.o: enumerator.cpp *.h
	g++ -c enumerator.cpp 