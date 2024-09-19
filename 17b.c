/*
============================================================================
Name : 17b.c
Author : Sakina Baranwala
Description : Write a program to execute ls -l | wc.
b. use dup2
Date: 19th September, 2024
============================================================================
*/







#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    int pid;

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
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        close(pipefd[1]);
        pid = fork();
        if (pid == 0) {
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);
            execlp("wc", "wc", NULL);
            perror("execlp");
            exit(EXIT_FAILURE);
        } else {
            close(pipefd[0]);
            wait(NULL);
            wait(NULL);
        }
    }

    return 0;
}


/*Output:
 *
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ gcc 17b.c -o 17b
sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./17b
     62     551    3064
*/
