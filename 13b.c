/*
============================================================================
Name : 13b.c
Author : Sakina Baranwala
Description : Write two programs: first program is waiting to catch SIGSTOP signal, the second program
will send the signal (using kill system call). Find out whether the first program is able to catch
the signal or not.

Program 2 : to send the stop signal
Date: 19th September, 2024
============================================================================
*/


#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PID>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int pid = atoi(argv[1]);

    printf("Sending SIGSTOP to PID %d\n", pid);
    kill(pid, SIGSTOP);

    return 0;
}



/*Output:
 *
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./13b 5613
Sending SIGSTOP to PID 5613
*/
