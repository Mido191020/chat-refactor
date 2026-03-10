//#include <iostream>
//using namespace std;
////send ->recive accapet/reject the request
////open port for network connection
////we should talke on the same port
////we need to pass os & network permissoin
////how the os open/allow you to establich the connection
////what happend ?how he understand that we need port how the verify happend
////what ,how sockets open /closed /how we could controle that
////what is role of hardwer here how things are linked and connected togther
////how our app can move the meesages what realy happend what is the os role
////I know the techinque of sending data over network
////how we can applay the linux arch that is build on files as the rquest response are files
////that we ovverwite on them /what is idea of everything is a file on linux
////how we can see how things works under the hood how things connected togther
//
//int port_number=-1;
//string connection_string=" ";
//int buffer=-1;
//int socket(int domain, int type, int protocol);
//void openconnection(){ static_assert("not implmented yet");}
//void openport(){ static_assert("not implmented yet");}
//void lisntPort(){ static_assert("not implmented yet");}


#if defined(_WIN32)
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#endif


#if defined(_WIN32)
#define ISVALIDSOCKET(s) ((s) != INVALID_SOCKET)
#define CLOSESOCKET(s) closesocket(s)
#define GETSOCKETERRNO() (WSAGetLastError())
#else
#define ISVALIDSOCKET(s) ((s) >= 0)
#define CLOSESOCKET(s) close(s)
#define SOCKET int
#define GETSOCKETERRNO() (errno)
#endif


#include <stdio.h>
#include <string.h>
#include <time.h>

int main()
{
#if defined(_WIN32)
    WSADATA d;
    if (WSAStartup(MAKEWORD(2, 2), &d)) {
        fprintf(stderr, "Failed to initialize.\n");
        return 1;
    }
#endif
    printf("Configuring local address...\n");
    struct addrinfo hints;
    memset(&hints,0,sizeof (hints));
    hints.ai_family=AF_INET;//IP4/IP6
    hints.ai_socktype=SOCK_STREAM;
    hints.ai_flags=AI_PASSIVE;
    struct addrinfo *bind_address;
    //genrate network adress
    getaddrinfo(NULL,"8080",&hints,&bind_address);
    printf("Creating socket...\n");
   // SOCKT socket_listen;
}
