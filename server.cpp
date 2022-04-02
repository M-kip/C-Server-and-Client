/*
 * Basic server program
 * Author: Moses kiprono
 * Date: 2 Apr 2022
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#define PORT 8080

/**
 * main - basic server program
 * @argc: Argument counter
 * @argv: Argument vector
 *
 * Return: 0
 */

int main(int argc, char *argv[])
{
    int sockfd, clientfd, rd;
    struct sockaddr_in addr;
    size_t addrlen = sizeof(addr);
    char buffer[1024] = {0};
    std::string msg ="hello from server";

    // create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        std::cout<<"Failed to create socket"<<std::endl;
        perror("socket error");
        exit(EXIT_FAILURE);
    }
    // populate addr struct
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);
    

    // bind socket
    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    // listen for incoming connections
    if (listen(sockfd, 5) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    // accept connections
    if ((clientfd = accept(sockfd, (struct sockaddr *)&addr, (socklen_t *)&addrlen)) < 0)
    {
        perror("Accept");
        exit(EXIT_FAILURE);
    }

    
    rd = read(clientfd, buffer, 1024);
    std::cout<<"Client message:" << buffer<<std::endl;
    send(clientfd, msg.c_str(), msg.size(),0);
    std::cout<< "Send message:"<<msg<<std::endl;

    close(clientfd);
    close(sockfd);

    return (0);
}