/*********************************************************************
 * Socket Class
 * @Filename: socket.cc
 * @Create:         Jack Lee@2016.08.18
 * @CreateEmail:    lizhongjie@cvte.com
 * @Modify:         Jack Lee@2016.08.25
 * @ModifyEmail:    lizhongjie@cvte.com
 * @Copyright(c) 2016 ~ . www.cvte.com All rights reserved.
*********************************************************************/


#include <iostream>

#include <errno.h>
#include <fcntl.h>

#include "socket.h"


Socket::~Socket()
{
    if(is_valid())  ::close(m_sockfd);
}

bool Socket::create()
{
    m_sockfd = ::socket(AF_INET, SOCK_STREAM, 0);

    if(!is_valid()) return false;

    int on = 1;
    if(::setsockopt(m_sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on)))   // return: 0 is success; -1 is wrong.
        return false;

    return true;
}

bool Socket::bind(const int port)
{
    if(!is_valid()) return false;

    m_addr.sin_family = AF_INET;
    m_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    m_addr.sin_port = htons(port);

    if(::bind(m_sockfd, (sockaddr *)&m_addr, sizeof(m_addr)))       // return: 0 is success; -1 is wrong.
        return false;

    return true;
}

bool Socket::listen() const
{
    if(!is_valid()) return false;

    if(::listen(m_sockfd, MAXCONNECTIONS))                          // return: 0 is success; -1 is wrong.
        return false;

    return true;
}

bool Socket::accept(Socket &client_socket) const
{
    socklen_t addr_len = sizeof(client_socket.m_addr);
    client_socket.m_sockfd = ::accept(m_sockfd, (sockaddr *)&client_socket.m_addr, &addr_len);

    if(!client_socket.is_valid())
        return false;

    return true;
}

bool Socket::connect(const std::string &host, const int port)
{
    if(!is_valid()) return false;

    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons(port);
    if(inet_pton(AF_INET, host.c_str(), &m_addr.sin_addr) != 1)     // return: 1 is success; 0 and -1 is wrong.
        return false;

    if(::connect(m_sockfd, (sockaddr *)&m_addr, sizeof(m_addr)))    // return: 0 is success; -1 is wrong.
        return false;

    return true;
}

bool Socket::send(const char *buf, const int len) const
{
    if(::send(m_sockfd, (void *)buf, len, MSG_NOSIGNAL) == -1)      // return: -1 is wrong.
        return false;

    return true;
}

bool Socket::send(const std::string &str) const
{
    return send(str.c_str(), str.size());
}

int Socket::recv(char *buf, const int len) const
{
    int ret_len = ::recv(m_sockfd, buf, len, 0);                    // return: -1 is wrong.

    if(ret_len == -1)
    {
        buf[0] = '\0';
        return -1;
    }
    else
    {
        buf[ret_len] = '\0';
        return ret_len;
    }
}

int Socket::recv(std::string &str) const
{
    char buf[MAXRECV + 1];

    str = "";

    int ret_len = recv(buf, MAXRECV);

    if(ret_len > 0)
        str = buf;

    return ret_len;
}

void Socket::set_non_blocking(const bool non_blocking)
{
    int opts;

    opts = fcntl(m_sockfd, F_GETFL);

    if(opts < 0)    return;

    if(non_blocking)
        opts = (opts | O_NONBLOCK);
    else
        opts = (opts & ~O_NONBLOCK);

    fcntl(m_sockfd, F_SETFL, opts);
}

