CXXFLAGS = -std=c++17
# CXXFLAGS += -fno-elide-constructors

FILES != ls *.cc
PROGS = $(FILES:R)
# Don't build man pages.
MAN =

# For every program, add its source file.
.for p in ${PROGS}
SRCS_$p += $p.cc
.endfor

# I need to copy this file hack.hpp.  I tried to add -I../, but this
# was crushing clang, when the parent directory was already built.
hack.hpp: ../hack.hpp
	cp ../hack.hpp .

all: hack.hpp $(PROGS)

.include <bsd.prog.mk>
