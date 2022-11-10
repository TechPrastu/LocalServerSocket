#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    try
    {
        // ClientSocket client_socket ( "localhost", 30000 );

        ClientSocket client_socket("/tmp/server_tmp");

        std::string reply;

        try
        {

            std::cout << "Enter data for server:";
            std::string newData;
            std::getline(std::cin, newData);
            client_socket << newData;
            client_socket >> reply;
        }
        catch (SocketException &)
        {
        }

        std::cout << "We received this response from the server:\n\"" << reply << "\"\n";
        ;
    }
    catch (SocketException &e)
    {
        std::cout << "Exception was caught:" << e.description() << "\n";
    }

    return 0;
}
