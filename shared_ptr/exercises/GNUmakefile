PROGS = $(patsubst %.cc, %, $(wildcard *.cc))
OBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

CXXFLAGS = -std=c++17 -I../../unique_ptr/exercises

all: $(PROGS) $(OBJS)
