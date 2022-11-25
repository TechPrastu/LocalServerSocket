#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include "Logger.h"

int main(int argc, char *argv[])
{
    Logger::SetPriority(LogLevel::INFO);

    Logger::Info( "%s", "running....");

    try
    {
        // Create the socket
        // ServerSocket server ( 30000 );
        unlink("/tmp/server_tmp");
        ServerSocket server("/tmp/server_tmp");

        while (true)
        {
            ServerSocket new_sock;
            server.accept(new_sock, false);

            try
            {
                while (true)
                {
                    std::string data;
                    new_sock >> data;
                    std::cout << "Server recv data from client is : " << data;
                    std::cout << std::endl;
                    std::cout << "Enter data for client:";
                    std::string newData;
                    std::getline(std::cin, newData);
                    new_sock << newData;
                }
            }
            catch (SocketException &)
            {
            }
        }
    }
    catch (SocketException &e)
    {
        std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }

    return 0;
}
