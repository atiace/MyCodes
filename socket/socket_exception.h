/*********************************************************************
 * SocketException Class
 * @Filename: socket_exception.h
 * @Create:         Jack Lee@2016.08.26
 * @CreateEmail:    lizhongjie@cvte.com
 * @Modify:         Jack Lee@2016.08.26
 * @ModifyEmail:    lizhongjie@cvte.com
 * @Copyright(c) 2016 ~ . www.cvte.com All rights reserved.
*********************************************************************/


#ifndef __SOCKET_EXCEPTION_H__
#define __SOCKET_EXCEPTION_H__


#include <string>


class SocketException
{
public:
    SocketException(const std::string &str) : m_str(str) {};
    ~SocketException() {};

    const std::string & description() { return m_str; }

private:
    std::string m_str;
};


#endif

