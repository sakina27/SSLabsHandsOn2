/*
============================================================================
Name : 21a.c
Author : Sakina Baranwala
Description : Write two programs so that both can communicate by FIFO -Use two way communications.

SENDER-RECIEVER PROGRAM

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
    int fd_write, fd_read;

    // Open FIFO1 for writing and FIFO2 for reading
    fd_write = open(FIFO1, O_WRONLY);
    fd_read = open(FIFO2, O_RDONLY);

    if (fd_write == -1 || fd_read == -1) {
        perror("Error opening FIFO");
        exit(1);
    }

    // Communication loop
    while (1) {
        printf("You: ");
        fgets(buffer, sizeof(buffer), stdin);

        // Write to FIFO1
        write(fd_write, buffer, strlen(buffer) + 1);

        // Wait for a response from FIFO2
        if (read(fd_read, buffer, sizeof(buffer)) > 0) {
            printf("Received: %s\n", buffer);
        }
    }

    close(fd_write);
    close(fd_read);
    return 0;
}


/*Output:
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./21a
You: Hi Terminal 1!
Received: Hi Terminal 2!

You: How are you doing Terminal 2?
Received: I am doing fine, how are you terminal 1?

You: I am also fine, okay bye
Received: bye
*/
