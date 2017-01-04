/*********************************************************************
 * ClientSocket Class
 * @Filename: client_socket.h
 * @Create:         Jack Lee@2016.08.26
 * @CreateEmail:    lizhongjie@cvte.com
 * @Modify:         Jack Lee@2016.08.26
 * @ModifyEmail:    lizhongjie@cvte.com
 * @Copyright(c) 2016 ~ . www.cvte.com All rights reserved.
*********************************************************************/


#ifndef __CLIENT_SOCKET_H__
#define __CLIENT_SOCKET_H__


#include "socket.cc"


class ClientSocket : private Socket
{
public:
    ClientSocket(const std::string server_addr, const int port);
    virtual ~ClientSocket() {};

    const ClientSocket & operator << (const std::string &) const;
    const ClientSocket & operator >> (std::string &) const;
};


#endif

