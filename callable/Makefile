PRGS = $(patsubst %.cc, %, $(wildcard *.cc))
ASMS = $(patsubst %.cc, %.s, $(wildcard *.cc))

CXXFLAGS = -std=c++20 -O3 -I../lib

all: $(PRGS) $(ASMS)

%.s: %.cc
	g++ ${CXXFLAGS} -S $< -o $@.tmp
	c++filt < $@.tmp > $@
	rm $@.tmp
