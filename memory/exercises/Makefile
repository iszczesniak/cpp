CXXFLAGS = -std=c++17
# Include the path to hack.hpp.
CXXFLAGS += -I../
# CXXFLAGS += -fno-elide-constructors

FILES != ls *.cc
PROGS = $(FILES:R)
# Don't build man pages.
MAN =

# For every program, add its source file.
.for p in ${PROGS}
SRCS_$p += $p.cc
.endfor

.include <bsd.prog.mk>
