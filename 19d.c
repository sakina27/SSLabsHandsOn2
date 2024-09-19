/*
============================================================================
Name : 19d.c
Author : Sakina Baranwala
Description : Create a FIFO file by
c. mknod system call
Date: 19th September, 2024
============================================================================
*/








#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
    const char *fifo_path = "my_fifo_mknod";

    if (mknod(fifo_path, S_IFIFO | 0666, 0) == -1) {
        perror("Error creating FIFO with mknod");
        exit(EXIT_FAILURE);
    }

    printf("FIFO file created with mknod.\n");
    return 0;
}


/*Output:
 *
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./19
FIFO file created with mknod.
*/
