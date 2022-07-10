#include "ServerClient/Include/ServerSocket.h"
#include "ServerClient/Include/SocketException.h"
#include <string>

int main ( int argc, char *argv[] )
{
    std::cout << "running....\n";

    try
    {
        // Create the socket
        // ServerSocket server ( 30000 );
        unlink( "/tmp/server_tmp" );
        ServerSocket server ( "/tmp/server_tmp" );

        while ( true )
        {

            ServerSocket new_sock;
            server.accept ( new_sock );

            try
            {
                while ( true )
                {
                    std::string data;
                    new_sock >> data;
                    std::cout << "Server recv data from client is : " << data << std::endl;
                    std::cout << "Enter data for client:";
                    std::string newData;
                    std::getline(std::cin, newData);
                    new_sock << newData;
                    std::cout << "enter data is --->" <<newData << std::endl;
                }
            }
            catch ( SocketException& ) {}

        }
    }
    catch ( SocketException& e )
    {
        std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }

    return 0;
}
