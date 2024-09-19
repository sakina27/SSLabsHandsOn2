/*
============================================================================
Name : 18.c
Author : Sakina Baranwala
Description : Write a program to find out total number of directories on the pwd.
execute ls -l | grep ^d | wc ? Use only dup2.
Date: 19th September, 2024
============================================================================
*/






#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefd1[2], pipefd2[2];
    pid_t pid1, pid2;

    if (pipe(pipefd1) == -1 || pipe(pipefd2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        close(pipefd1[0]);
        dup2(pipefd1[1], STDOUT_FILENO);
        close(pipefd1[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        close(pipefd1[1]);
        dup2(pipefd1[0], STDIN_FILENO);
        close(pipefd1[0]);
        close(pipefd2[0]);
        dup2(pipefd2[1], STDOUT_FILENO);
        close(pipefd2[1]);
        execlp("grep", "grep", "^d", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    close(pipefd1[0]);
    close(pipefd1[1]);
    close(pipefd2[1]);
    dup2(pipefd2[0], STDIN_FILENO);
    close(pipefd2[0]);
    execlp("wc", "wc", "-l", NULL);
    perror("execlp");
    exit(EXIT_FAILURE);

    return 0;
}


/*Output:
 *
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./18
0
sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ mkdir tmp
sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ mkdir tmp1
sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ mkdir tmp2
sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./18
3
*/
