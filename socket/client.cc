/*********************************************************************
 * Client Main
 * @Filename: client.cc
 * @Create:         Jack Lee@2016.08.26
 * @CreateEmail:    lizhongjie@cvte.com
 * @Modify:         Jack Lee@2016.08.26
 * @ModifyEmail:    lizhongjie@cvte.com
 * @Copyright(c) 2016 ~ . www.cvte.com All rights reserved.
*********************************************************************/


#include <string>
#include <iostream>

#include "client_socket.cc"


const std::string kServer_Address = "172.17.82.165";


int main(int argc, char *argv[])
{
    try
    {
        ClientSocket client_socket(kServer_Address, 30000);

        std::string str;

        try
        {
            client_socket << "Test message.";
            client_socket >> str;
        }
        catch(SocketException &) {}

        std::cout << "We received this response from the server:\n\"" << str << "\"" << std::endl;
    }
    catch(SocketException & e)
    {
        std::cout << "Exception was caught: " << e.description() << std::endl;
    }

    return 0;
}

