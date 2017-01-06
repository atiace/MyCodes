/*********************************************************************
 * Socket Class
 * @Filename: socket.h
 * @Create:         Jack Lee@2016.08.18
 * @CreateEmail:    lizhongjie@cvte.com
 * @Modify:         Jack Lee@2016.08.25
 * @ModifyEmail:    lizhongjie@cvte.com
 * @Copyright(c) 2016 ~ . www.cvte.com All rights reserved.
*********************************************************************/


#ifndef __SOCKET_H__
#define __SOCKET_H__


#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>


const int MAXCONNECTIONS = 5;
const int MAXRECV = 2048;


class Socket
{
public:
    Socket() : m_sockfd(-1) {}
    virtual ~Socket();

    // Server
    bool create();
    bool bind(const int);
    bool listen() const;
    bool accept(Socket &) const;

    // Client
    bool connect(const std::string &, const int);

    // Data Transmit
    bool send(const char *, const int) const;
    bool send(const std::string &) const;
    int recv(char *, const int) const;
    int recv(std::string &) const;

    void set_non_blocking(const bool);

    bool is_valid() const { return m_sockfd != -1; }

private:
    int m_sockfd;
    sockaddr_in m_addr;
};


#endif

