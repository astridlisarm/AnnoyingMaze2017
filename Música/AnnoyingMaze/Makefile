ALEPH = /home/astrid/Escritorio/ALEPH/Aleph-w

CLANGPATH=/usr/bin

CXX = $(CLANGPATH)/clang++-3.9 -std=c++14

OPTIMIZATION = -O0

WARN = -Wall -Wextra -Wcast-align -Wno-sign-compare \
	-Wno-write-strings -Wno-parentheses 

FLAGS = -DDEBUG -D_GLIBCXX__PTHREADS -g $(OPTIMIZATION) -std=c++14 \
	$(WARN)

INCLUDE = -I. -I $(ALEPH) 

LIBS = -L $(ALEPH) \
       -lAleph -lc -lm -lgsl -lgslcblas -lgmp -lmpfr -lasprintf  \
	-lpthread -lnana

default: all

all: maze

maze: maze.C
	$(CXX) $(FLAGS_DEBUG) $(INCLUDE) $@.C -o $@ $(LIBS)

maze-op: maze.C
	$(CXX) $(FLAGS_RELEASE) $(INCLUDE) maze.C -o $@ $(LIBS)

clean:
	$(RM) *~ maze maze-op



