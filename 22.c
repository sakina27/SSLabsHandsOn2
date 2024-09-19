/*
============================================================================
Name : 22.c
Author : Sakina Baranwala
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select
system call with FIFO.
Date: 20th September, 2024
============================================================================
*/







#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#define FIFO_PATH "my_fifo"
#define BUFFER_SIZE 100

int main() {
    int fd;
    char buffer[BUFFER_SIZE];
    fd_set readfds;
    struct timeval timeout;

    // Create FIFO if it doesn't exist
    if (mkfifo(FIFO_PATH, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    // Open FIFO for reading in non-blocking mode
    fd = open(FIFO_PATH, O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Initialize the file descriptor set
    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);

    // Set the timeout to 10 seconds
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    // Wait for data to be written into FIFO or timeout
    int retval = select(fd + 1, &readfds, NULL, NULL, &timeout);

    if (retval == -1) {
        perror("select");
        close(fd);
        exit(EXIT_FAILURE);
    } else if (retval == 0) {
        printf("No data written within 10 seconds.\n");
    } else {
        if (FD_ISSET(fd, &readfds)) {
            int bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
            if (bytes_read == -1) {
                perror("read");
                close(fd);
                exit(EXIT_FAILURE);
            }
            buffer[bytes_read] = '\0'; // Null-terminate the string
            printf("Data read from FIFO: %s\n", buffer);
        }
    }

    close(fd);
    return 0;
}


/*Output:
 *
 * Case 1 : When the data is written 
 * Terminal 1:
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./21
Data read from FIFO: Hello! from fifo file

   Terminal 2:
   sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ echo "Hello! from fifo file" > my_fifo
sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$


   Case 2: When no data is written
sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./21
No data written within 10 seconds.
*/
