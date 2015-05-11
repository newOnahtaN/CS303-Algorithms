CPP      = g++
CPPFLAGS = -c -g -Wall -pedantic -std=c++11 -O3

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -o $@ $<

SRC = union_find0.cpp union_find1.cpp union_find2.cpp
H   = union_find0.hpp union_find1.hpp union_find2.hpp

all: dependencies foo0 foo1 foo2

dependencies: $(SRC) $(H)
	 rm -f dependencies
	 $(CC) $(CPPFLAGS) -MM $(SRC) >> dependencies

include dependencies

foo0: union_find0.o 
	g++ -o $@ -g -pg union_find0.o

foo1: union_find1.o 
	g++ -o $@ -g -pg union_find1.o

foo2: union_find2.o 
	g++ -o $@ -g -pg union_find2.o 

clean: 
	rm dependencies union_find0.o union_find1.o union_find2.o foo0 foo1 foo2
