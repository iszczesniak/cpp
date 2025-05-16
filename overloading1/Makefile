SRCS_CC != ls *.cc
PROGS = $(SRCS_CC:R)

SRCS_CPP != ls *.cpp
OBJS = $(SRCS_CPP:cpp=o)

CXX = clang++-19

CXXFLAGS = -std=c++23

all: $(PROGS) $(OBJS)
