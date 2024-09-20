/*
============================================================================
Name : 34a.c
Author : Sakina Baranwala
Description : Write a program to create a concurrent server.
              a. use fork
Date: 20th September, 2024
============================================================================
*/





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/wait.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    int bytes_read;

    while ((bytes_read = read(client_socket, buffer, BUFFER_SIZE)) > 0) {
        printf("Client: %s", buffer);
        send(client_socket, buffer, bytes_read, 0);
    }
    close(client_socket);
    exit(0);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }

        if (fork() == 0) {
            close(server_fd);  
            handle_client(client_socket);
        } else {
            close(client_socket);  
            waitpid(-1, NULL, WNOHANG);  
        }
    }

    close(server_fd);
    return 0;
}


/*Output:
 *
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./34a
Client: Hi Server, This is Client1!
Client: Hi Server! This is Client 2
Client: Hi Server! Message from client 3
Client: Client 1 is sending message to server
Client: client 2 is sending message to server

CLIENT1:

sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./33b
You: Hi Server, This is Client1!
Server: Hi Server, This is Client1!

You: Client 1 is sending message to server
Server: Client 1 is sending message to server

CLIENT2:

sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./33b
You: Hi Server! This is Client 2
Server: Hi Server! This is Client 2

You: client 2 is sending message to server
Server: client 2 is sending message to server

CLIENT3:
sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./33b
You: Hi Server! Message from client 3
Server: Hi Server! Message from client 3

*/
