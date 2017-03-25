CC=gcc
RM=rm -r -f
LDLIBRARIES=-lredox_static -lev -lhiredis -pthread -I../include -L../build
CPPFILES=server.cpp \
        ../socket/message.cpp ../socket/header.cpp ../socket/socket.cpp
OUTPUT=server
TARGET=server
all : $(TARGET)
server : $(OUTPUT)
    $(CC) $(CPPFILES) -o $(OUTPUT) $(LDLIBRARIES)
clean:
    $(RM) $(OUTPUT)
