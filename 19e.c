/*
============================================================================
Name : 19e.c
Author : Sakina Baranwala
Description : Create a FIFO file by
              e. mkfifo library function
Date: 19th September, 2024
============================================================================
*/



#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
    const char *fifo_path = "my_fifo_mkfifo";

    if (mkfifo(fifo_path, 0666) == -1) {
        perror("Error creating FIFO with mkfifo");
        exit(EXIT_FAILURE);
    }

    printf("FIFO file created with mkfifo.\n");
    return 0;
}



/*Output:
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./19e
FIFO file created with mkfifo.
*/
