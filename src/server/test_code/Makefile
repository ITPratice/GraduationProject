simple_server_objects = ServerSocket.o socket.o server.o
simple_client_objects = ClientSocket.o socket.o client.o


all : simple_server simple_client

simple_server: $(simple_server_objects)
        g++ -o simple_server $(simple_server_objects)


simple_client: $(simple_client_objects)
        g++ -o simple_client $(simple_client_objects)


Socket: socket.cpp
ServerSocket: ServerSocket.cpp
ClientSocket: ClientSocket.cpp
simple_server_main: server.cpp
simple_client_main: client.cpp


clean:
        rm -f *.o simple_server simple_client
