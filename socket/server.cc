/*********************************************************************
 * Server Main
 * @Filename: server.cc
 * @Create:         Jack Lee@2016.08.26
 * @CreateEmail:    lizhongjie@cvte.com
 * @Modify:         Jack Lee@2016.08.26
 * @ModifyEmail:    lizhongjie@cvte.com
 * @Copyright(c) 2016 ~ . www.cvte.com All rights reserved.
*********************************************************************/


#include <iostream>
#include <string>

#include "server_socket.cc"


int main(int argc, char *argv[])
{
    std::cout << "running....\n";

    try
    {
        ServerSocket server(30000);

        while(true)
        {
            ServerSocket connect_socket;
            server.accept(connect_socket);

            try
            {
                while(true)
                {
                    std::string str;
                    connect_socket >> str;
                    std::cout << "Server Transfer: " << str << std::endl;
                    connect_socket << str;
                }
            }
            catch (SocketException &) {}
        }
    }
    catch(SocketException & e)
    {
        std::cout << "Exception was caught: " << e.description() << std::endl << "\tExiting." << std::endl;
    }

    return 0;
}

