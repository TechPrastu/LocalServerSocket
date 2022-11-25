// Implementation of the ServerSocket class

#include "ServerSocket.h"
#include "SocketException.h"
#include "Logger.h"

ServerSocket::ServerSocket ( int port )
{
    Logger::Trace("%s: port:%d", __func__, port );

    if ( ! Socket::create() )
    {
        throw SocketException ( "Could not create server socket." );
    }

    if ( ! Socket::bind ( port ) )
    {
        throw SocketException ( "Could not bind to port." );
    }

    if ( ! Socket::listen() )
    {
        throw SocketException ( "Could not listen to socket." );
    }
}

ServerSocket::ServerSocket ( std::string serverPath)
{
    Logger::Trace("%s: serverPath:%s", __func__, serverPath );

    if ( ! Socket::create( serverPath ) )
    {
        throw SocketException ( "Could not create server socket." );
    }

    if ( ! Socket::bind ( serverPath ) )
    {
        throw SocketException ( "Could not bind to port." );
    }

    if ( ! Socket::listen() )
    {
        throw SocketException ( "Could not listen to socket." );
    }
}

ServerSocket::~ServerSocket()
{
    Logger::Trace("%s", __func__ );
}

const ServerSocket& ServerSocket::operator << ( const std::string& s ) const
{
    if ( ! Socket::send ( s ) )
    {
        throw SocketException ( "Could not write to socket." );
    }

    return *this;

}

const ServerSocket& ServerSocket::operator >> ( std::string& s ) const
{
    if ( ! Socket::recv ( s ) )
    {
        throw SocketException ( "Could not read from socket." );
    }

    return *this;
}

void ServerSocket::accept ( ServerSocket& sock, const bool &blocking )
{
    Logger::Trace("%s", __func__ );

    if ( ! Socket::accept ( sock ) )
    {
        throw SocketException ( "Could not accept socket." );
    }

    Socket::set_non_blocking( blocking );
}
