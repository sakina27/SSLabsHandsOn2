/*
============================================================================
Name : 9.c
Author : Sakina Baranwala
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT
signal - Use signal system call.
Date: 19th September, 2024
============================================================================
*/




#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler(int signum) {
    printf("SIGINT signal received (this should not happen initially).\n");
}

int main() {
    signal(SIGINT, SIG_IGN);
    printf("SIGINT is being ignored. Press Ctrl+C.\n");

    sleep(5);

    signal(SIGINT, SIG_DFL);
    printf("SIGINT action reset to default. Press Ctrl+C now.\n");

    while (1) {
        printf("Running... (Press Ctrl+C to terminate)\n");
        sleep(1);
    }

    return 0;
}


/*Output:
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./9
SIGINT is being ignored. Press Ctrl+C.
^C



SIGINT action reset to default. Press Ctrl+C now.
Running... (Press Ctrl+C to terminate)
Running... (Press Ctrl+C to terminate)
Running... (Press Ctrl+C to terminate)
Running... (Press Ctrl+C to terminate)
Running... (Press Ctrl+C to terminate)
^C
sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ */
