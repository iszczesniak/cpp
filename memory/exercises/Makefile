CXXFLAGS = -std=c++17 -I../../lib
# CXXFLAGS += -fno-elide-constructors

FILES != ls *.cc
PROGS = $(FILES:R)
# Don't build man pages.
MAN =

# Extra files used by those programs.
SRCS_example1 = A.cpp

# For every program, add its source file.
.for p in ${PROGS}
SRCS_$p += $p.cc
.endfor

A.cpp: ../../lib/A.cpp
	cp ../../lib/A.cpp .

.include <bsd.prog.mk>
