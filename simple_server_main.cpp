#include "ServerSocket.h"
#include "SocketException.h"
#include <string>

int main ( int argc, int argv[] )
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
                    std::cin >> data;
                    new_sock << data;
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
