/*
============================================================================
Name : 16.c
Author : Sakina Baranwala
Description : Write a program to send and receive data from parent to child vice versa. Use two way
communication.
Date: 19th September, 2024
============================================================================
*/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int parentToChild[2], childToParent[2];
    int pid;
    char parentMessage[] = "Message from parent";
    char childMessage[] = "Reply from child";
    char buffer[100];

    if (pipe(parentToChild) == -1 || pipe(childToParent) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        close(parentToChild[1]);
        close(childToParent[0]);

        ssize_t bytesRead = read(parentToChild[0], buffer, sizeof(buffer) - 1);
        if (bytesRead < 0) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        buffer[bytesRead] = '\0';
        printf("Child received: %s\n", buffer);

        write(childToParent[1], childMessage, strlen(childMessage) + 1);

        close(parentToChild[0]);
        close(childToParent[1]);
        exit(0);
    } else {
        close(parentToChild[0]);
        close(childToParent[1]);

        write(parentToChild[1], parentMessage, strlen(parentMessage) + 1);

        ssize_t bytesRead = read(childToParent[0], buffer, sizeof(buffer) - 1);
        if (bytesRead < 0) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        buffer[bytesRead] = '\0';
        printf("Parent received: %s\n", buffer);

        close(parentToChild[1]);
        close(childToParent[0]);
        wait(NULL);
    }

    return 0;
}



/*Output:
 *
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./16
Child received: Message from parent
Parent received: Reply from child
*/
