PRGS = $(patsubst %.cc, %, $(wildcard *.cc))
PRGS = $(patsubst %.cc, %.s, $(wildcard *.cc))

CXXFLAGS = -std=c++2a

all: $(PRGS)

%.s: %.cc
	g++ ${CXXFLAGS} -S $<
