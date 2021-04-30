CXX=g++
CXXFLAGS=-g -Wall -std=c++11
# Uncomment for parser DEBUG
#DEFS=-DDEBUG

OBJS= counting.o

all: counting

counting: $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ $(OBJS)

counting.o: bayes.cpp
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c counting.cpp


clean:
	rm -f *.o counting