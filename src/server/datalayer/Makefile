CC      	= g++
CFLAGS  	= -I. -c -Wall -fPIC
LDFLAGS 	= -Wall -shared -lpthread -o
EXFLAGS		= -lstdc++ -lsqlite3 -lboost_system -lcrypto -lssl -lcpprest -Wall -lpthread

SOURCES		= 	data_manager.cpp \
			user.cpp \
			history.cpp \
			location.cpp \
			vehicle.cpp \
			vehicle_type.cpp \
			branch.cpp

all: $(SOURCES) test.cpp
		$(CC) $(SOURCES) test.cpp $(EXFLAGS) -o test

clean:
	rm -rf test

test: $(SOURCES) test.cpp
		$(CC) $(SOURCES) test.cpp $(EXFLAGS) -o test