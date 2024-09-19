/*
============================================================================
Name : 15.c
Author : Sakina Baranwala
Description : Write a simple program to send some data from parent to the child process.
Date: 19th September, 2024
============================================================================
*/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    int pid;
    char message[] = "Hello from the parent process!";
    char buffer[100];

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
        close(pipefd[1]);
        ssize_t bytesRead = read(pipefd[0], buffer, sizeof(buffer) - 1);
        if (bytesRead < 0) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        buffer[bytesRead] = '\0';
        printf("Child process received: %s\n", buffer);
        close(pipefd[0]);
        exit(0);
    } else {
        close(pipefd[0]);
        write(pipefd[1], message, strlen(message) + 1);
        close(pipefd[1]);
        wait(NULL);
    }

    return 0;
}



/*Output:
 *
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./15
Child process received: Hello from the parent process!*/
