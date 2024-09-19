/*
============================================================================
Name : 23.c
Author : Sakina Baranwala
Description : Write a program to print the maximum number of files can be opened within a process and
size of a pipe (circular buffer).
Date: 20th September, 2024
============================================================================
*/






#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    long max_files = sysconf(_SC_OPEN_MAX);
    printf("Maximum number of files that can be opened within a process: %ld\n", max_files);

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    int pipe_size = fpathconf(pipefd[1], _PC_PIPE_BUF);
    if (pipe_size == -1) {
        perror("fpathconf");
    } else {
        printf("Pipe buffer size (according to _PC_PIPE_BUF): %d bytes\n", pipe_size);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    return 0;
}




/*Output:
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./23
Maximum number of files that can be opened within a process: 1024
Pipe buffer size (according to _PC_PIPE_BUF): 4096 bytes
*/
