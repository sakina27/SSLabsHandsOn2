/*
============================================================================
Name : 20a.c
Author : Sakina Baranwala
Description : Write two programs so that both can communicate by FIFO -Use one way communication.

WRITER PROGRAM

Date: 20th September, 2024
============================================================================
*/






#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_PATH "my_fifo"

int main() {
    int fd;
    const char *message = "Hello from writer!";

    fd = open(FIFO_PATH, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if (write(fd, message, strlen(message)) == -1) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);
    printf("Message written to FIFO.\n");

    return 0;
}


/*Output:
 *
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./20a
Message written to FIFO.
*/
