FILES != ls *.cc
PROGS = $(FILES:R)
# Don't build man pages.
MAN =

# Extra files used by those programs.
SRCS_args = A.cpp
SRCS_mcc = A.cpp
SRCS_placement = A.cpp
SRCS_return = A.cpp

# For every program, add its source file.
.for p in ${PROGS}
SRCS_$p += $p.cc
.endfor

CXXFLAGS = -std=c++17

.include <bsd.prog.mk>
