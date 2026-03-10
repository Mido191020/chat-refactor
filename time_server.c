//
// Created by HUAWEI on 3/5/2026.
//
//#include <iostream>
//using namespace std;
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
//#include <string>
#include <string.h>
#include <time.h>

void print(char s[]){
    fprintf(stderr,s,GETSOCKETERRNO());

}
int main(){
#if defined(_WIN32)
    WSADATA d;
    if (WSAStartup(MAKEWORD(2,2),&d)){
        fprintf(stderr,"Failed to initialize.\n");
    }
#endif
    printf("Configuring local address...\n");
    struct addrinfo hints;
    memset(&hints,0,sizeof (hints));
    hints.ai_family=AF_INET;
    hints.ai_socktype=SOCK_STREAM;
    //REFRECH MY MEMORY ABOUT THIS
    hints.ai_flags=AI_PASSIVE;
    //hints vs bind_adress?
    struct addrinfo*bind_address;

    //I am lost here on the order

    getaddrinfo(0,"8080",&hints,&bind_address);

    printf("Creating socket...\n");
    SOCKET socket_listin;
    socket_listin=socket(bind_address->ai_family,
                         bind_address->ai_socktype,
                            bind_address->ai_protocol
                          );

    if (ISVALIDSOCKET(socket_listin)){
        print("\"Failed to initialize Socket.\\n");
       // fprintf(stderr,"Failed to initialize Socket.\n",GETSOCKETERRNO());
        return 1;
    }

    printf("Binding socket to local address...\n");

    if (bind(socket_listin,bind_address->ai_addr,bind_address->ai_addrlen)){
        print("bind() failed. (%d)\\n");
        return 1;
    }
    freeaddrinfo(bind_address);
    printf("Listening...\n");
    if (listen(socket_listin,10)<0){
        print("listen() failed. (%d)\n");
        return 1;
    }

    printf("Waiting for connection...\n");
    struct sockaddr_storage client_address;
    socklen_t client_len=sizeof (client_address);
    SOCKET client_sockt= accept(socket_listin,
                                ( struct sockaddr*)&client_address,
                                        &client_len
                                );
    if(!ISVALIDSOCKET(client_sockt)){
        print("accept faild () \n");
        return 1;
    }

    printf("Client is connected... ");
    char address_buffer[100];
    getnameinfo((struct sockaddr*)&client_address,
                client_len,
                address_buffer,
                sizeof (address_buffer),
                0,
                0,
                NI_NUMERICHOST
            );
    printf("%s\n", address_buffer);
    printf("Reading request...\n");
    char request[1024];
    int bytes_received= recv(client_len,address_buffer,1024,0);
    printf("Received %d bytes.\n", bytes_received);
    printf("%.*s", bytes_received, request);

    printf("Sending response...\n");
    const char *response=
            "HTTP/1.1 200 OK\\r\\n "
            "Connection: close\\r\\n"
            "Content-Type: text/plain\\r\\n\\r\\n"
            "Local time is: ";
    int bytes_sent = send(client_sockt, response, strlen(response), 0);
    printf("Sent %d of %d bytes.\n", bytes_sent, (int)strlen(response));
    time_t timer;
    time(&timer);
    char *time_msg= ctime(&timer);
    bytes_sent=send(client_sockt,time_msg, strlen(time_msg),0);
    printf("Sent %d of %d bytes.\n", bytes_sent, (int)strlen(time_msg));
    printf("Closing connection...\n");

    printf("Closing listening socket...\n");
    CLOSESOCKET(client_sockt);
#if defined(_WIN32)
    WSACleanup();
#endif
    printf("Finished.\n");
    return 0;
}