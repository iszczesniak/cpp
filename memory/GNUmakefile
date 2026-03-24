PROGS = $(patsubst %.cc, %, $(wildcard *.cc))

CXXFLAGS = -std=c++17
#CXXFLAGS += -fno-elide-constructors

all: A.o $(PROGS)

LDFLAGS = A.o
