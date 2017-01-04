/*********************************************************************
 * ClientSocket Class
 * @Filename: client_socket.cc
 * @Create:         Jack Lee@2016.08.26
 * @CreateEmail:    lizhongjie@cvte.com
 * @Modify:         Jack Lee@2016.08.26
 * @ModifyEmail:    lizhongjie@cvte.com
 * @Copyright(c) 2016 ~ . www.cvte.com All rights reserved.
*********************************************************************/


#include "client_socket.h"
#include "socket_exception.h"


ClientSocket::ClientSocket(const std::string server_addr, const int port)
{
    if(!Socket::create())
    {
        throw SocketException("Could not create client socket.");
    }

    if(!Socket::connect(server_addr, port))
    {
        throw SocketException("Could not bind to port.");
    }
}

const ClientSocket & ClientSocket::operator << (const std::string & str) const
{
    if(!Socket::send(str))
    {
        throw SocketException("Could not write to socket.");
    }

    return *this;
}

const ClientSocket & ClientSocket::operator >> (std::string & str) const
{
    if(!Socket::recv(str))
    {
        throw SocketException("Could not read from socket.");
    }

    return *this;
}

