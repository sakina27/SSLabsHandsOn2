/*
============================================================================
Name : 17b.c
Author : Sakina Baranwala
Description : Write a program to execute ls -l | wc.
c. use fcntl
Date: 19th September, 2024
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    int pid1, pid2;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid1 = fork();
    if (pid1 == 0) {
        int flags = fcntl(pipefd[1], F_GETFD);
        fcntl(pipefd[1], F_SETFD, flags | FD_CLOEXEC);
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    pid2 = fork();
    if (pid2 == 0) {
        int flags = fcntl(pipefd[0], F_GETFD);
        fcntl(pipefd[0], F_SETFD, flags | FD_CLOEXEC);
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        execlp("wc", "wc", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    close(pipefd[0]);
    close(pipefd[1]);
    wait(NULL);
    wait(NULL);

    return 0;
}


/*Output:
 *
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./17c
     64     569    3166
*/
