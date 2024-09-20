/*
============================================================================
Name : 34a.c
Author : Sakina Baranwala
Description : Write a program to create a concurrent server.
              b. use pthread_create
Date: 20th September, 2024
============================================================================
*/




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void *handle_client(void *arg) {
    int client_socket = *(int*)arg;
    char buffer[BUFFER_SIZE] = {0};
    int bytes_read;

    while ((bytes_read = read(client_socket, buffer, BUFFER_SIZE)) > 0) {
        printf("Client: %s", buffer);
        send(client_socket, buffer, bytes_read, 0);
    }
    close(client_socket);
    free(arg);
    pthread_exit(NULL);
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

        int *client_sock_ptr = malloc(sizeof(int));
        *client_sock_ptr = client_socket;

        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_client, client_sock_ptr) != 0) {
            perror("Failed to create thread");
        }
        pthread_detach(thread_id);  // Automatically reclaim resources after thread exits
    }

    close(server_fd);
    return 0;
}


/*Output:
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./34b
Client: Hi Server! This is client 3
Client: Hi Server! Sending message from client 2
Client: Hi Server! This message is from client 1


CLIENT1:
sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./33b
You: Hi Server! This message is from client 1
Server: Hi Server! This message is from client 1

You:

CLIENT2:
sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./33b
You: Hi Server! Sending message from client 2
Server: Hi Server! Sending message from client 2

You:


CLIENT3:
sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./33b
You: Hi Server! This is client 3
Server: Hi Server! This is client 3

You: */
