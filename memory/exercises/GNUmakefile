CXXFLAGS = -std=c++17 -I../
# Include the path to hack.hpp.
CXXFLAGS += -I../
#CXXFLAGS += -fno-elide-constructors

PROGS = $(patsubst %.cc, %, $(wildcard *.cc))

all: $(PROGS)
