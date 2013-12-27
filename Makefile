RCEXTS = .c .C .cc .cpp .c++ .cxx .cp 
HDREXTS = .h .H .hh .hpp .h++ .hxx .hp 
LIBS = 
CC = gcc 
CXX = g++
INCLUDES = 
CFLAGS = -g -Wall -fPIC -c $(INCLUDES)
OFLAGS = -g -shared -Wall
APP = GC.so

SRCDIR = .
SRCS = $(wildcard $(SRCDIR)/*.cc $(SRCDIR)/*.cpp)
OBJS = $(addsuffix .o, $(basename $(SRCS)))
HEADS = $(addsuffix .h, $(basename $(SRCS)))

$(APP) : $(OBJS)
	$(CXX) $(OFLAGS) -o $@ $^

%.o:%.cc
	$(CXX) $(CFLAGS) -o $@ $<

%.o:%.cpp
	$(CXX) $(CFLAGS) -o $@ $<

clean :
	rm -rf *.o
	rm -rf *.so
