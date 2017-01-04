/*********************************************************************
 * ServerSocket Class
 * @Filename: server_socket.h
 * @Create:         Jack Lee@2016.08.19
 * @CreateEmail:    lizhongjie@cvte.com
 * @Modify:         Jack Lee@2016.08.26
 * @ModifyEmail:    lizhongjie@cvte.com
 * @Copyright(c) 2016 ~ . www.cvte.com All rights reserved.
*********************************************************************/


#ifndef __SERVER_SOCKET_H__
#define __SERVER_SOCKET_H__


#include "socket.cc"


class ServerSocket : private Socket
{
public:
    ServerSocket(const int);
    ServerSocket() {};
    virtual ~ServerSocket();

    const ServerSocket & operator << (const std::string &) const;
    const ServerSocket & operator >> (std::string &) const;

    void accept(ServerSocket &);
};


#endif

