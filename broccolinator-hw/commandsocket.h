#ifndef COMMANDSOCKET_H
#define COMMANDSOCKET_H
#include <sys/un.h>

enum COMMANDS
{
    CMD_CONNECT,
    CMD_WEIGHT,
    CMD_OK,
    CMD_KO,
    CMD_PROCESSING,
    CMD_ERROR=-1
};

enum EVENTS
{
    EVT_WEIGHT,
    EVT_START
};

struct EVENT_DATA 
{
    EVENTS event;
    union
    {
        struct
        {
            int weight;
        } weight;
    };
};

class CommandSocket
{
    protected:
    
        int cmd_socket;
        sockaddr_un clientaddr;
        bool connected;

    public:
        
        CommandSocket();
        ~CommandSocket();

        // opens command socket
        bool init();

        // return fd for select
        int get_fd();

        // reads a command from the socket
        COMMANDS get_command();

        // sends an event
        bool send_event(EVENT_DATA* evt);
};

#endif
