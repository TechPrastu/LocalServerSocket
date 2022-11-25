// Implementation of the ClientSocket class

#include "ClientSocket.h"
#include "SocketException.h"
#include "Logger.h"


ClientSocket::ClientSocket ( std::string host, int port )
{
    Logger::Trace("%s: host:%s, port:%d", __func__, host, port );

    if ( ! Socket::create() )
    {
        throw SocketException ( "Could not create client socket." );
    }

    if ( ! Socket::connect ( host, port ) )
    {
        throw SocketException ( "Could not bind to port." );
    }
}

ClientSocket::ClientSocket ( std::string serverPath )
{
    Logger::Trace("%s: serverPath:%s", __func__, serverPath );

    if ( ! Socket::create( serverPath ) )
    {
        throw SocketException ( "Could not create client socket." );
    }

    if ( ! Socket::connect ( serverPath ) )
    {
        throw SocketException ( "Could not bind to serverPath " + serverPath );
    }
}


const ClientSocket& ClientSocket::operator << ( const std::string& s ) const
{
    if ( ! Socket::send ( s ) )
    {
        throw SocketException ( "Could not write to socket." );
    }

    return *this;

}


const ClientSocket& ClientSocket::operator >> ( std::string& s ) const
{
    if ( ! Socket::recv ( s ) )
    {
        throw SocketException ( "Could not read from socket." );
    }

    return *this;
}
