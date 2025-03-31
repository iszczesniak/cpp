SRCS_CC != ls *.cc
PROGS = $(SRCS_CC:R)

SRCS_CPP != ls *.cpp
OBJS = $(SRCS_CPP:cpp=o)

CXXFLAGS = -std=c++17

all: $(PROGS) $(OBJS)
