PRGS = $(patsubst %.cc, %, $(wildcard *.cc))
ASMS = $(patsubst %.cc, %.s, $(wildcard *.cc))

CXXFLAGS = -std=c++2a

all: $(PRGS) $(ASMS)

%.s: %.cc
	g++ ${CXXFLAGS} -S $< -o $@.tmp
	c++filt < $@.tmp > $@
