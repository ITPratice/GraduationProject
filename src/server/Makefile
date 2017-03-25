CC=g++
RM=rm -r -f
LDFLAGS=-std=c++11
LDLIBRARIES=-lredox_static -lev -lhiredis -pthread -I../include -L../build
CPPFILES=main.cpp
OUTPUT=main
TARGET=main
all : $(TARGET)
main : 
	$(CC) $(CPPFILES) -o $(OUTPUT) $(LDFLAGS) $(LDLIBRARIES)
clean:
	$(RM) $(OUTPUT)