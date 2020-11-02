#include "commandsocket.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
        
CommandSocket::CommandSocket()
{
    cmd_socket=-1;
    connected=false;
    memset(&clientaddr,0,sizeof(sockaddr_un));
}

CommandSocket::~CommandSocket()
{
    if (cmd_socket!=-1) {
        close(cmd_socket);
    }
}

bool CommandSocket::init() 
{
    cmd_socket=socket(AF_UNIX,SOCK_DGRAM, 0);

    if (cmd_socket==-1)
    {
        return false;
    }

    sockaddr_un addr;

    memset(&addr,0,sizeof(addr));

    addr.sun_family=AF_UNIX;
    strcpy(addr.sun_path,"/tmp/broccolinator_hw");

    unlink(addr.sun_path);

    if (bind(cmd_socket, (struct sockaddr*)&addr, sizeof(addr)))
    {
        return false;
    }
    return true;
}

int CommandSocket::get_fd()
{
    return cmd_socket;
}

COMMANDS CommandSocket::get_command()
{
    COMMANDS cmd;
    socklen_t addrlen=sizeof(sockaddr_un);

    if (recvfrom(cmd_socket,&cmd,sizeof(COMMANDS),0,(sockaddr*)&clientaddr,&addrlen)<0)
    {
        return CMD_ERROR;
    }
    connected=true;
    return cmd;
}

bool CommandSocket::send_event(EVENT_DATA* evt)
{
    if (!connected) 
    {
        return true;
    }

    if (sendto(cmd_socket,evt,sizeof(EVENT_DATA),0,(const sockaddr*)&clientaddr,(socklen_t)sizeof(sockaddr_un))<0)
    {
        return false;
    }
    return true;
}
