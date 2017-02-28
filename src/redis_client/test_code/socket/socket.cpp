// Implementation of the Socket class.

#include "socket.h"
#include <string.h>
#include <errno.h>
#include <fcntl.h>

Socket::Socket() : m_sock(-1) {
    memset(&m_addr, 0, sizeof(m_addr));
}

Socket::~Socket() {
    if (is_valid())
        ::close(m_sock);
}

bool Socket::create() {
    m_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (!is_valid())
        return false;
    // TIME_WAIT - argh
    int on = 1;
    if (setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, (const char *)&on, sizeof(on)) == -1)
        return false;
    return true;
}

bool Socket::bind(const int port) {
    if (!is_valid()) {
        return false;
    }
    m_addr.sin_family = AF_INET;
    m_addr.sin_addr.s_addr = INADDR_ANY;
    m_addr.sin_port = htons(port);
    int bind_return = ::bind(m_sock, (struct sockaddr *)&m_addr, sizeof(m_addr));
    if (bind_return == -1) {
        return false;
    }
    return true;
}

bool Socket::listen() const {
    if (!is_valid()) {
        return false;
    }
    int listen_return = ::listen(m_sock, MAXCONNECTIONS);
    if (listen_return == -1) {
        return false;
    }
    return true;
}

bool Socket::accept(Socket &new_socket) const {
    int addr_length = sizeof(m_addr);
    new_socket.m_sock = ::accept(m_sock, (sockaddr *)&m_addr, (socklen_t *)&addr_length);
    if (new_socket.m_sock <= 0)
        return false;
    else
        return true;
}

bool Socket::send ( const std::string s ) const {
    std::cout << "Socket::Send string = " << s << ";";
    unsigned int size = s.size();
    int status = send((char*)&size, sizeof(unsigned int));

    status = send(s.c_str(), s.size());
    //std::cout << status << std::endl;
    return status == (int)s.size();
}

int Socket::send (const char* bytes, const unsigned int& size) const {
    //std::cout << "Socket::Send bsize=" << size << ",last byte=" << bytes[size - 1] << std::endl;
    unsigned int out_bytes = 0;

    while (out_bytes < size) {
        // std::cout << "before write to socket: <<  " << size - out_bytes << "\n";
        int n = ::write(m_sock, bytes + out_bytes, size - out_bytes);
        if (n < 0){
            //printf("[ERROR] Unable to send reponse.\n");
            std::cout << "[ERROR] Unable to send reponse.\n";
            close(m_sock);
            return -1;
        } else
            if (n == 0) { // connection closed!
                //printf("[ERROR] Connection has been unexpectedly closed by remote side!\n");
                std::cout <<"[ERROR] Connection has been unexpectedly closed by remote side!\n";
                close(m_sock);
                return -2;
            } else {
                out_bytes += n;
                //printf("Socket sent (%d bytes).\n", n);
                //std::cout << "Socket sent (" << n << " bytes).\n";
            }
    }
    return out_bytes;
}

bool Socket::send (const Message& msg ) const {
    //std::cout << "Socket::Send message\n";
    // Send header
    char* hdr; unsigned int hdr_size;

    const Header * header = msg.GetHeader();
    Header::GetBytes(*header, &hdr, &hdr_size);
    //std::cout << "header size = " << hdr_size << std::endl;

    if(send(hdr, hdr_size) != (int)hdr_size){
        //printf("send header fail\n");
        std::cout << "[ERR]Socket::Send send message header fail\n";
        delete[] hdr;
        return false;
    }
    delete[] hdr;

    // Send data
    //std::cout << "begin send message data\n";
    const char *data = msg.GetData();
    unsigned int data_size = msg.GetHeader()->GetDataSize();
    if(data != NULL && data_size > 0){
        if(send(data, data_size) != (int)data_size){
            //printf("send message data fail.");
            std::cout << "[ERR]Socket::Send message data fail.\n";
            return false;
        } else {
            //printf("send message data success.");
            //std::cout << "send message data success.";
        }
    } else {
        //printf("Message data is emtpy\n");
        //std::cout << "Message data is emtpy\n";
    }
    return true;
}

int Socket::recv(std::string &s) const {
    char buf [ MAXRECV + 1 ];
    s = "";
    memset ( buf, 0, MAXRECV + 1 );

    unsigned int sot = 0;
    int status = recv((char*)&sot, sizeof(unsigned int));

    if(sot > 0){
        status = recv (buf, sot);
        //std::cout << status << std::endl;
        if ( status > 0 ) {
            s = buf;
        }
    }
    return status;
}

int Socket::recv (char* buffer, unsigned int size) const {
    unsigned int in_bytes = 0;
    while(in_bytes < size){
        int n = ::read(m_sock, buffer + in_bytes, size - in_bytes);
        if (n < 0){
            //printf("[ERROR] Unable to recv.\n");
            std::cout << "[ERROR] Unable to recv.\n" ;
            close(m_sock);
            return -1;
        } else
            if (n == 0) { // connection closed!
                //printf("[ERROR] Connection has been unexpectedly closed by remote side!\n");
                std::cout << "[ERROR] Connection has been unexpectedly closed by remote side!\n";
                close(m_sock);
                return -2;
            } else {
                in_bytes += n;
                //printf("Socket receieve (%d bytes).\n", n);
                //std::cout << "Socket receieve ("<< n << " bytes).\n";
            }
    }
    return in_bytes;
}

int Socket::recv(Message& msg) const {
    std::cout << "Socket::Recv ";

    // Read header
    int hdr_size = sizeof(Header);
    char* buf = new char[hdr_size];
    int in_size = recv(buf,hdr_size);
    if(in_size != hdr_size) {
        std::cout << "error receieve header\n";
        delete []buf;
        return in_size;
    }
    int msg_type, command;
    unsigned int from_port, to_port, data_size;
    int offset = 0;
    memcpy(&msg_type, buf + offset, sizeof(int));
    offset += sizeof(int);
    memcpy(&from_port, buf + offset, sizeof(unsigned int));
    offset += sizeof(unsigned int);
    memcpy(&to_port, buf + offset, sizeof(unsigned int));
    offset += sizeof(unsigned int);
    memcpy(&data_size, buf + offset, sizeof(unsigned int));
    offset += sizeof(unsigned int);
    memcpy(&command, buf + offset, sizeof(int));

    delete []buf;
    buf = NULL;

    if(data_size > 0){
        buf = new char[data_size];
        int status = recv(buf, data_size);
        if(status!= (int)data_size){
            std::cout << "error receieve data\n";
            delete []buf;
            return status;
        }
    }

    //std::cout <<"create message from byte.\n";
    std::cout << "type=" << msg_type << ",from port=" << from_port << ",to port=" << to_port << ",data size="<< data_size << ",command = " << command << std::endl;
    Header hdr((MessageTypes)msg_type, from_port, to_port, data_size,(Commands)command);
    msg.SetHeader(hdr);
    msg.SetData(buf);

    //std::cout << "rev message success\n";
    return data_size + hdr_size;
}

bool Socket::connect(const std::string host, const int port) {
    if (!is_valid())
        return false;
    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons(port);
    int status = inet_pton(AF_INET, host.c_str(), &m_addr.sin_addr);
    if (errno == EAFNOSUPPORT)
        return false;
    status = ::connect(m_sock, (sockaddr *)&m_addr, sizeof(m_addr));
    if (status == 0)
        return true;
    else
        return false;
}

void Socket::set_non_blocking(const bool b)
{
    int opts;
    opts = fcntl(m_sock, F_GETFL);
    if (opts < 0) {
        return;
    }

    if (b)
        opts = (opts | O_NONBLOCK);
    else
        opts = (opts & ~O_NONBLOCK);

    fcntl(m_sock, F_SETFL, opts);
}
