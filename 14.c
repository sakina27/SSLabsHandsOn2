/*
============================================================================
Name : 14.c
Author : Sakina Baranwala
Description : Write a simple program to create a pipe, write to the pipe, read from pipe and display on
the monitor.
Date: 19th September, 2024
============================================================================
*/






#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int pipefd[2];
    int pid;
    char buffer[100];

    printf("Creating pipe..\n");

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        close(pipefd[0]);
        const char *message = "Hello from the child process!";

	printf("Writing to the pipe..\n");
        write(pipefd[1], message, strlen(message)+1);
        close(pipefd[1]);
        exit(0);
    } else {
        close(pipefd[1]);
        ssize_t bytesRead = read(pipefd[0], buffer, sizeof(buffer) - 1);
        if (bytesRead < 0) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        buffer[bytesRead] = '\0';
        printf("Parent process read: %s\n", buffer);
        close(pipefd[0]);
        wait(NULL);
    }

    return 0;
}




/*Output:
 *
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./14
Creating pipe..
Writing to the pipe..
Parent process read: Hello from the child process!
*/
