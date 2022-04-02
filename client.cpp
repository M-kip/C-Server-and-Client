/*
 * Program to steal directory information
 * Author: Moses Kiprono
 * Date 2 Apr 2022
 */

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8000

/**
 * main - Create socket and connects to server
 * @argv: cmd arguments
 * @argc : argument counter
 *
 * Return: 0
 */

int main(int argc, char *argv[])
{
    struct sockaddr_in serv_addr;
    int sockfd;
    std::string msg;
    char buffer[1024];

    if((sockfd = socket(AF_INET,SOCK_STREAM, 0)) < 0)
    {
        std::cout<<"Error failed to create socket";
        exit(EXIT_FAILURE);
    }
    
    // populate addr
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("172.0.0.1");

    // connect to server
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cout<<"Failed to connect to server\n";
        perror("Failure");
        exit(EXIT_FAILURE);
    }

    msg = "welcome to the server \n";
    send(sockfd, msg.c_str(), msg.size(), 0);
    std::cout<<msg.c_str();
    read(sockfd, buffer, 1024);
    std::cout<<buffer;

    close(sockfd);

    return (0);
}
