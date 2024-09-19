/*
============================================================================
Name : 12.c
Author : Sakina Baranwala
Description : Write a program to create an orphan process. Use kill system call to send SIGKILL signal to
the parent process from the child process.
Date: 19th September, 2024
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
int main() {
    int pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        sleep(1);
        int parent_pid = getppid();
        printf("Child process: My PID is %d, parent PID is %d\n", getpid(), parent_pid);
        kill(parent_pid, SIGKILL);
        while (1) {
            printf("Child process is now an orphan and continues running...\n");
            sleep(2);
	    pause();
        }
    } else {
        printf("Parent process: My PID is %d, child PID is %d\n", getpid(), pid);
        sleep(5);
        printf("Parent process exiting...\n");
        exit(0);
    }
    return 0;
}


/*Output:
 *
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./12
Parent process: My PID is 5273, child PID is 5274
Child process: My PID is 5274, parent PID is 5273
Child process is now an orphan and continues running...
Killed*/
