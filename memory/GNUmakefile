CXXFLAGS = -std=c++17 -I../lib
#CXXFLAGS += -fno-elide-constructors

PROGS = $(patsubst %.cc, %, $(wildcard *.cc))

LDFLAGS = A.o

all: A.o $(PROGS)

A.cpp: ../lib/A.cpp
	cp ../lib/A.cpp .
