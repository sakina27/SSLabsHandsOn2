/*
============================================================================
Name : 33b.c
Author : Sakina Baranwala
Description : Write a program to communicate between two machines using socket.
CLIENT CODE
Date: 20th September, 2024
============================================================================
*/




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        printf("Socket creation error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Invalid address/ Address not supported\n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection Failed\n");
        return -1;
    }

    while (1) {
        printf("You: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        send(sock, buffer, strlen(buffer), 0);
        int bytes_read = read(sock, buffer, BUFFER_SIZE);
        buffer[bytes_read] = '\0';
        printf("Server: %s\n", buffer);
    }

    close(sock);
    return 0;
}


/*Output:
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./33b
You: Hi Server!
Server: Hi Server!

You: Message from server
Server: Message from server

You:
*/
