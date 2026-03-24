FILES != ls *.cc
PROGS = $(FILES:R)
# Don't build man pages.
MAN =

# Extra files used by those programs.
SRCS_anywhere = A.cpp
SRCS_args = A.cpp
SRCS_dynamic = A.cpp
SRCS_elide = A.cpp
SRCS_global = A.cpp
SRCS_local = A.cpp
SRCS_materialization1 = A.cpp
SRCS_materialization2 = A.cpp
SRCS_placement = A.cpp
SRCS_return = A.cpp
SRCS_static = A.cpp

# For every program, add its source file.
.for p in ${PROGS}
SRCS_$p += $p.cc
.endfor

CXXFLAGS = -std=c++17
# CXXFLAGS += -fno-elide-constructors

.include <bsd.prog.mk>
