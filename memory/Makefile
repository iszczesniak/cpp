CXXFLAGS = -std=c++17 -I../lib
# CXXFLAGS += -fno-elide-constructors

FILES != ls *.cc
PROGS = $(FILES:R)
# Don't build man pages.
MAN =

# Extra files used by those programs.
SRCS_anywhere = A.cpp
SRCS_args = A.cpp
SRCS_dynamic = A.cpp
SRCS_implementation = A.cpp
SRCS_initialization = A.cpp
SRCS_no_elision1 = A.cpp
SRCS_no_elision2 = A.cpp
SRCS_no_elision3 = A.cpp
SRCS_global = A.cpp
SRCS_local = A.cpp
SRCS_materialization = A.cpp
SRCS_named = A.cpp
SRCS_parameter = A.cpp
SRCS_placement = A.cpp
SRCS_return = A.cpp
SRCS_standalone = A.cpp
SRCS_static = A.cpp
SRCS_unnamed = A.cpp

# For every program, add its source file.
.for p in ${PROGS}
SRCS_$p += $p.cc
.endfor

A.cpp: ../lib/A.cpp
	cp ../lib/A.cpp .

.include <bsd.prog.mk>
