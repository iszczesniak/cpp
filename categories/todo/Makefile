CXXFLAGS = -std=c++17
# CXXFLAGS += -fno-elide-constructors

FILES != ls *.cc
PROGS = $(FILES:R)
# Don't build man pages.
MAN =

# Extra files used by those programs.
SRCS_lvalue-to-prvalue = A.cpp
SRCS_prvalue-to-lvalue = A.cpp
SRCS_prvalue-to-xvalue = A.cpp
SRCS_xvalue-to-prvalue = A.cpp

# For every program, add its source file.
.for p in ${PROGS}
SRCS_$p += $p.cc
.endfor

A.cpp: ../../lib/A.cpp
	cp ../../lib/A.cpp .

A.hpp: ../../lib/A.hpp
	cp ../../lib/A.hpp .

all: A.hpp A.cpp

.include <bsd.prog.mk>
