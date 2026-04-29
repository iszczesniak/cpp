CXXFLAGS = -std=c++17 -I../lib
#CXXFLAGS += -fno-elide-constructors

PROGS = $(patsubst %.cc, %, $(wildcard *.cc))

LDFLAGS = A.o

all: A.hpp A.o $(PROGS)

A.hpp: ../lib/A.hpp
	cp ../lib/A.hpp .

A.cpp: ../lib/A.cpp
	cp ../lib/A.cpp .
