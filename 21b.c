/*
============================================================================
Name : 21b.c
Author : Sakina Baranwala
Description : Write two programs so that both can communicate by FIFO -Use two way communications.

RECIEVER-SENDER PROGRAM

Date: 20th September, 2024
============================================================================
*/







#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO1 "fifoFile1"
#define FIFO2 "fifoFile2"

int main() {
    char buffer[1024];
    int fd_read, fd_write;

    // Open FIFO1 for reading and FIFO2 for writing
    fd_read = open(FIFO1, O_RDONLY);
    fd_write = open(FIFO2, O_WRONLY);

    if (fd_read == -1 || fd_write == -1) {
        perror("Error opening FIFO");
        exit(1);
    }

    // Communication loop
    while (1) {
        // Read from FIFO1 (blocking until a message is available)
        if (read(fd_read, buffer, sizeof(buffer)) > 0) {
            printf("Received: %s\n", buffer);

            // Prepare response
            printf("You: ");
            fgets(buffer, sizeof(buffer), stdin);

            // Write to FIFO2
            write(fd_write, buffer, strlen(buffer) + 1);
        }
    }

    close(fd_write);
    close(fd_read);
    return 0;
}


/*Output:
 *
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./21b
Received: Hi Terminal 1!

You: Hi Terminal 2!
Received: How are you doing Terminal 2?

You: I am doing fine, how are you terminal 1?
Received: I am also fine, okay bye

You: bye


*/
