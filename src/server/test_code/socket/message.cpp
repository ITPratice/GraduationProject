#include "message.hpp"
Message::Message(){
    m_data = NULL;
}

Message::Message(Header hdr, char* data){
    m_header = hdr;
    m_data = data;
}

Message::~Message(){
    if(m_data != NULL && m_header.GetDataSize() > 0){
        delete[] m_data;
    }
}

const Header* Message::GetHeader() const{
    return &m_header;
}

void Message::SetHeader(const Header &hdr){
    m_header = hdr;
}

void Message::SetData(char* buf){
    m_data = buf;
}

char* Message::GetData() const {
    return m_data;
}

int Message::SetArgs(char *args, char **argv)
{
    int count = 0;

    while (isspace(*args)) ++args;
    while (*args) {
        if (argv)
            argv[count] = args;
        while (*args && !isspace(*args))
            ++args;
        if (argv && *args)
            *args++ = '\0';
        while (isspace(*args))
            ++args;
        count++;
    }
    return count;
}

char ** Message::ParsedArgs(char *args, int *argc) {
    char **argv = NULL;
    int    argn = 0;

    if (args && *args
            && (args = strdup(args))
            && (argn = SetArgs(args,NULL))
            && (argv = (char**)malloc((argn+1) * sizeof(char *)))) {
        *argv++ = args;
        argn = SetArgs(args,argv);
    }

    if (args && !argv) free(args);

    *argc = argn;
    return argv;
}

void Message::FreeParsedArgs(char **argv) {
    if (argv) {
        std::cout << "Message::FreeParsedArgs argv[-1],";
        free(argv[-1]);
        std::cout << "free(argv-1),";
        free(argv-1);
        std::cout << " success\n";
    }
}

void Message::ToBytes(char **bytes, unsigned int &msg_size) const {
    Header c_hdr(m_header);
    msg_size = 0;
    char* hdr = reinterpret_cast<char*>(&c_hdr);
    msg_size = sizeof(Header) + (unsigned int)c_hdr.GetDataSize();
    *bytes = new char[msg_size];

    memcpy(*bytes, hdr, sizeof(Header));
    if(m_data != NULL && c_hdr.GetDataSize() > 0){
        memcpy(*bytes + sizeof(Header), m_data, c_hdr.GetDataSize());
    } else {
    }
}

void Message::AddArgv(const char* cmd_arg, int cmd_arg_size){
    if(cmd_arg_size <= 0)
        return;
    unsigned int cur_ds = m_header.GetDataSize();

    char * tmp = NULL;
    if(cur_ds != 0){
        tmp = new char[cur_ds + cmd_arg_size + 1];
        memcpy(tmp, m_data, cur_ds);
        tmp[cur_ds] = CMD_SEPERATOR_CHAR;
        cur_ds ++; // for seperator char
        delete[] m_data;
        m_data = NULL;
    } else {
        tmp = new char[cmd_arg_size];
    }
    memcpy(tmp + cur_ds, cmd_arg, cmd_arg_size);
    m_data = tmp;
    m_header.SetDataSize(cur_ds + cmd_arg_size);
}

void Message::AddArgv(const std::string &cmd_arg){
    AddArgv(cmd_arg.c_str(), cmd_arg.size());
}

void Message::AddArgv(int cmd_arg){
    std::stringstream ss;
    ss << cmd_arg;
    std::string cmd_arg_str = ss.str();
    AddArgv(cmd_arg_str.c_str(), cmd_arg_str.size());
}

std::vector<std::string> Message::GetCmdArgs(){
    std::cout << "Message::GetCmdArgs ";
    std::vector<std::string> argv, sub_strs;
    if(m_header.GetDataSize()<= 0){
        std::cout << " no argument.\n";
        return argv;
    }

    char* data_str = new char[m_header.GetDataSize() + 1];
    memcpy(data_str, m_data, m_header.GetDataSize());
    data_str[m_header.GetDataSize()] = '\0';
    std::cout <<"m_data:" << data_str << std::endl;

    // Parse args
    std::string data(data_str);
    Split(data,CMD_SEPERATOR_CHAR, &argv);

    std::cout << " argc=" << argv.size() << ":";
    for(unsigned int i = 0; i < argv.size(); i ++){
        std::cout << argv[i] << " ";
    }
    std::cout << std::endl;

    delete[]data_str;
    return argv;
}

