%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c -o $@ $<

CPP = g++
CPPFLAGS = -g -std=c++11 -Wall -pedantic 

foo: main.o array.o
	g++ -g -std=c++11 -o quicksort main.o array.o

main.o: main.cpp array.hpp

array.o: array.cpp array.hpp