// Definition of the ServerSocket class

#ifndef ServerSocket_class
#define ServerSocket_class

#include "Socket.h"

class ServerSocket : private Socket
{
public:
    ServerSocket ( int port );
    ServerSocket ( std::string );
    ServerSocket (){};
    virtual ~ServerSocket();

    const ServerSocket& operator << ( const std::string& ) const;
    const ServerSocket& operator >> ( std::string& ) const;

    void accept ( ServerSocket&, const bool &blocking = false );
};


#endif
