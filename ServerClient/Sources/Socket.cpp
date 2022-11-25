// Implementation of the Socket class.
#include "Socket.h"
#include "string.h"
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include "Logger.h"

Socket::Socket() : m_sock ( -1 )
{
    Logger::Trace("%s", __func__ );

    memset ( &m_addr, 0, sizeof ( m_addr ) );
    memset(&serveraddr, 0, sizeof(serveraddr));
}

Socket::~Socket()
{
    Logger::Trace("%s", __func__ );

    if ( is_valid() )
        ::close ( m_sock );
}

bool Socket::create()
{
    Logger::Trace("%s", __func__ );

    m_sock = socket ( AF_INET, SOCK_STREAM, 0 );

    if ( ! is_valid() )
        return false;

    // TIME_WAIT - argh
    int on = 1;
    if ( setsockopt ( m_sock, SOL_SOCKET, SO_REUSEADDR, ( const char* ) &on, sizeof ( on ) ) == -1 )
        return false;

    return true;
}

bool Socket::create( const std::string serverPath )
{
    Logger::Trace("%s: serverPath:%s", __func__, serverPath );

    m_sock = socket(AF_UNIX, SOCK_STREAM, 0);

    if ( ! is_valid() )
        return false;

    //    if( setsockopt(m_sock, SOL_SOCKET, SO_RCVLOWAT, (char *)&BUFFER_LENGTH, sizeof(BUFFER_LENGTH)) == -1)
    //        return false;

    int on = 1;
    if ( setsockopt ( m_sock, SOL_SOCKET, SO_REUSEADDR, ( const char* ) &on, sizeof ( on ) ) == -1 )
        return false;

    return true;
}

bool Socket::bind ( const int port )
{
    Logger::Trace("%s: port:%d", __func__, port );

    if ( ! is_valid() )
    {
        return false;
    }

    m_addr.sin_family = AF_INET;
    m_addr.sin_addr.s_addr = INADDR_ANY;
    m_addr.sin_port = htons ( port );

    int bind_return = ::bind ( m_sock, ( struct sockaddr * ) &m_addr, sizeof ( m_addr ) );

    if ( bind_return == -1 )
    {
        return false;
    }

    return true;
}

bool Socket::bind ( const std::string serverPath)
{
    Logger::Trace("%s: serverPath:%s", __func__, serverPath );

    if ( ! is_valid() )
    {
        return false;
    }

    serveraddr.sun_family = AF_UNIX;
    strcpy( serveraddr.sun_path, serverPath.c_str() );

    int bind_return = ::bind ( m_sock, (struct sockaddr *)&serveraddr, SUN_LEN(&serveraddr) );

    if ( bind_return == -1 )
    {
        return false;
    }

    return true;
}

bool Socket::listen() const
{
    Logger::Trace("%s", __func__ );

    if ( ! is_valid() )
    {
        return false;
    }

    int listen_return = ::listen ( m_sock, MAXCONNECTIONS );


    if ( listen_return == -1 )
    {
        return false;
    }

    return true;
}


bool Socket::accept ( Socket& new_socket ) const
{
    Logger::Trace("%s", __func__ );

    int addr_length = sizeof ( m_addr );
    new_socket.m_sock = ::accept ( m_sock, ( sockaddr * ) &m_addr, ( socklen_t * ) &addr_length );

    if ( new_socket.m_sock <= 0 )
        return false;
    else
        return true;
}


bool Socket::send ( const std::string sendData ) const
{
    Logger::Trace("%s: sendData:%s", __func__, sendData );

    int status = ::send ( m_sock, sendData.c_str(), sendData.size(), MSG_NOSIGNAL );
    if ( status == -1 )
    {
        return false;
    }
    else
    {
        return true;
    }
}


int Socket::recv ( std::string& recvData ) const
{
    Logger::Trace("%s: recvData:%s", __func__, recvData );

    char buf [ MAXRECV + 1 ];

    recvData = "";

    memset ( buf, 0, MAXRECV + 1 );

    int status = ::recv ( m_sock, buf, MAXRECV, 0 );

    if ( status == -1 )
    {
        std::cout << "status == -1   errno == " << errno << "  in Socket::recv\n";
        return 0;
    }
    else if ( status == 0 )
    {
        return 0;
    }
    else
    {
        recvData = buf;
        return status;
    }
}

bool Socket::connect ( const std::string host, const int port )
{
    Logger::Trace("%s: host:%s, port:%s", __func__, host, port );

    if ( ! is_valid() ) return false;

    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons ( port );

    int status = inet_pton ( AF_INET, host.c_str(), &m_addr.sin_addr );

    if ( errno == EAFNOSUPPORT ) return false;

    status = ::connect ( m_sock, ( sockaddr * ) &m_addr, sizeof ( m_addr ) );

    if ( status == 0 )
        return true;
    else
        return false;
}

bool Socket::connect ( const std::string serverPath)
{
    Logger::Trace("%s: serverPath:%s", __func__, serverPath );

    if ( ! is_valid() )
        return false;

    serveraddr.sun_family = AF_UNIX;
    strcpy( serveraddr.sun_path, serverPath.c_str() );

    int status = ::connect(m_sock, (struct sockaddr *)&serveraddr, SUN_LEN(&serveraddr));

    if ( status == 0 )
        return true;
    else
        return false;
}

void Socket::set_non_blocking ( const bool b )
{
    Logger::Trace("%s", __func__ );

    int opts;

    opts = fcntl ( m_sock, F_GETFL );

    if ( opts < 0 )
    {
        return;
    }

    if ( b )
        opts = ( opts | O_NONBLOCK );
    else
        opts = ( opts & ~O_NONBLOCK );

    fcntl ( m_sock, F_SETFL,opts );

}
