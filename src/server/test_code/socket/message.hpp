#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <sstream>
#include <cctype>
#include "header.hpp"

#define CMD_SEPERATOR_CHAR '#'

class Message {
private:
    Header m_header;
    char* m_data;
public:
    Message();
    Message(Header hdr, char* data);
    ~Message();
    const Header* GetHeader() const;
    void SetHeader(const Header &hdr);
    char* GetData() const;
    void SetData(char*buf);
    void ToBytes(char **bytes, unsigned int &msg_size) const;
    void AddArgv(const std::string &cmd_arg);
    void AddArgv(int cmd_arg);
    void AddArgv(const char* cmd_arg, int cmd_arg_size);
    std::vector<std::string> GetCmdArgs();
private:
    char** GetCmdArgs(int& argc);
    void FreeParsedArgs(char **argv);
    int SetArgs(char *args, char **argv);
    char ** ParsedArgs(char *args, int *argc);
    inline void Split(const std::string &str, char del,
                      std::vector<std::string> *out) {
        std::istringstream ss(str);
        std::string s;
        while (std::getline(ss, s, del)) {
            out->push_back(s);
        }
    }
};

#endif
