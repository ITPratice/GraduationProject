CC      	= g++
CFLAGS  	= -I. -c -Wall -fPIC
LDFLAGS 	= -Wall -shared -lpthread -o
EXFLAGS		= -lstdc++ -lsqlite3 -lboost_system -lcrypto -lssl -lcpprest -Wall -lpthread -std=c++11

SOURCES		= 	datalayer/data_manager.cpp datalayer/user.cpp datalayer/location.cpp datalayer/vehicle.cpp \
			datalayer/vehicle_type.cpp datalayer/branch.cpp \
			handler/branch/branch_handler.cpp \
			handler/location/location_handler.cpp \
			handler/user/user_handler.cpp \
			handler/vehicle/vehicle_handler.cpp \
			handler/vehicle_type/vehicle_type_handler.cpp \
			handler/current_time/current_time_handler.cpp \
			handler/user/all_user_handler.cpp \
			handler/location/current_location_handler.cpp \
			handler/arduino/location.cpp \
			handler/user/login_handler.cpp	\
			handler/user/login_admin_handler.cpp \
			handler/vehicle/vehicleplate_byuser_handler.cpp \
			handler/user/active_user_handler.cpp

all: $(SOURCES) main.cpp
		$(CC) $(SOURCES) main.cpp $(EXFLAGS) -o main

clean:
	rm -rf main