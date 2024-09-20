/*
============================================================================
Name : 20b.c
Author : Sakina Baranwala
Description : Write two programs so that both can communicate by FIFO -Use one way communication.

READER PROGRAM

Date: 20th September, 2024
============================================================================
*/





#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO_PATH "my_fifo"
#define BUFFER_SIZE 100

int main() {
    int fd;
    char buffer[BUFFER_SIZE];

    fd = open(FIFO_PATH, O_RDONLY);
    if (fd == -1) {
        perror("Error opening FIFO for reading");
        exit(EXIT_FAILURE);
    }

    if (read(fd, buffer, BUFFER_SIZE) == -1) {
        perror("Error reading from FIFO");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);

    printf("Message read from FIFO: %s\n", buffer);

    return 0;
}


/*Output:
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./20b
Message read from FIFO: Hello from writer!
*/
