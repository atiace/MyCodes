/*********************************************************************
 * ServerSocket Class
 * @Filename: server_socket.cc
 * @Create:         Jack Lee@2016.08.19
 * @CreateEmail:    lizhongjie@cvte.com
 * @Modify:         Jack Lee@2016.08.26
 * @ModifyEmail:    lizhongjie@cvte.com
 * @Copyright(c) 2016 ~ . www.cvte.com All rights reserved.
*********************************************************************/


#include "server_socket.h"
#include "socket_exception.h"


ServerSocket::ServerSocket(const int port)
{
    if(!Socket::create())
    {
        throw SocketException("Could not create server socket.");
    }

    if(!Socket::bind(port))
    {
        throw SocketException("Could not bind to port.");
    }

    if(!Socket::listen())
    {
        throw SocketException("Could not listen to socket.");
    }
}

ServerSocket::~ServerSocket()
{
}

const ServerSocket & ServerSocket::operator << (const std::string & str) const
{
    if(!Socket::send(str))
    {
        throw SocketException("Could not write to socket.");
    }

    return *this;
}

const ServerSocket & ServerSocket::operator >> (std::string & str) const
{
    if(!Socket::recv(str))
    {
        throw SocketException("Could not read from socket.");
    }

    return *this;
}

void ServerSocket::accept(ServerSocket &sock)
{
    if(!Socket::accept(sock))
    {
        throw SocketException("Could not accept socket.");
    }
}

