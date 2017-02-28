#ifndef HEADER_HPP
#define HEADER_HPP
#include <stdio.h>
#include <string.h>
#include <iostream>
enum MessageTypes
{
    MT_COMMAND,
    MT_DATA
};

enum Commands
{
    CMD_TEST,
    CMD_SEND_REQUEST
};

class Header
{
private:
    MessageTypes m_type;
    unsigned int m_from_port;
    unsigned int m_to_port;
    unsigned int m_data_size;
    Commands m_command;
    //unsigned int m_argc;
public:
    Header();
    Header(MessageTypes type, unsigned int from_port, unsigned int to_port, unsigned int data_size, Commands command);
    Header(const Header& cp);
    ~Header();

    MessageTypes GetType() const;
    void SetType(const MessageTypes type);
    void SetDataSize(const unsigned int data_size);
    unsigned int GetDataSize() const;

    void SetFromPort(const unsigned int from_port);
    unsigned int GetFromPort() const;

    void SetToPort(const unsigned int from_port);
    unsigned int GetToPort() const;

    void SetCommand(const Commands command);
    Commands GetCommand() const;

    //char** GetCommandArgs();

    //void SetArgc(const unsigned int argc) ;
    //unsigned int GetArgc() const;


    unsigned int GetCommandArgc() const;
    void SetCommandArgc(const unsigned int argc) ;

    //static char * ToBytes(const Header& hdr);
    static void GetBytes(const Header& hdr, char ** bytes, unsigned int* size);
    //static Header* FromBytes(const char* bytes, Header& hdr);
};

#endif
