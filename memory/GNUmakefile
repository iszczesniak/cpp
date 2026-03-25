CXXFLAGS = -std=c++17
#CXXFLAGS += -fno-elide-constructors

PROGS = $(patsubst %.cc, %, $(wildcard *.cc))

LDFLAGS = A.o

all: A.o $(PROGS)
