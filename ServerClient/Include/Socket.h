// Definition of the Socket class

#ifndef Socket_class
#define Socket_class

#include <stdio.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>
#include <iostream>

const int BUFFER_LENGTH = 250;
const int MAXHOSTNAME = 200;
const int MAXCONNECTIONS = 5;
const int MAXRECV = 500;

class Socket
{
public:
    Socket();
    virtual ~Socket();

    // Server initialization
    bool create();
    bool create ( const std::string );
    bool bind ( const int port );
    bool bind ( const std::string );
    bool listen() const;
    bool accept ( Socket& ) const;

    // Client initialization
    bool connect ( const std::string host, const int port );
    bool connect ( const std::string );

    // Data Transimission
    bool send ( const std::string ) const;
    int recv ( std::string& ) const;

    void set_non_blocking ( const bool );

    bool is_valid() const
    {
        return m_sock != -1;
    }

private:

    int m_sock;
    sockaddr_in m_addr;
    sockaddr_un serveraddr;
};

#endif
