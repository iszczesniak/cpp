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

hack.hpp: ../hack.hpp
	cp ../hack.hpp .

.include <bsd.prog.mk>
