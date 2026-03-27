CXXFLAGS = -std=c++17
#CXXFLAGS += -fno-elide-constructors

PROGS = $(patsubst %.cc, %, $(wildcard *.cc))

LDFLAGS = A.o

A.hpp: ../lib/A.hpp
	cp ../lib/A.hpp .

A.cpp: ../lib/A.cpp
	cp ../lib/A.cpp .

all: A.hpp A.o $(PROGS)
