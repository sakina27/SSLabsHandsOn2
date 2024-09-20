/*
============================================================================
Name : 30.c
Author : Sakina Baranwala
Description : Write a program to create a shared memory.
a. write some data to the shared memory
b. attach with O_RDONLY and check whether you are able to overwrite.
c. detach the shared memory
d. remove the shared memory
Date: 20th September, 2024
============================================================================
*/







#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>

jmp_buf jump_buffer;

void handle_segmentation_fault(int sig) {
    printf("Segmentation fault caught! Cannot write to read-only shared memory.\n");
    longjmp(jump_buffer, 1);
}

int main() {
    signal(SIGSEGV, handle_segmentation_fault);

    int key = ftok("shmfile", 65);
    int shmid;
    char *data;

    shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        return 1;
    }

    data = (char*) shmat(shmid, NULL, 0);
    if (data == (char*)-1) {
        perror("shmat failed");
        return 1;
    }

    printf("Writing data to shared memory...\n");
    strcpy(data, "Hello, Shared Memory!");

    if (shmdt(data) == -1) {
        perror("shmdt failed");
        return 1;
    }

    data = (char*) shmat(shmid, NULL, SHM_RDONLY);
    if (data == (char*)-1) {
        perror("shmat failed (read-only)");
        return 1;
    }

    printf("Reading from shared memory: %s\n", data);

    if (setjmp(jump_buffer) == 0) {
        printf("Attempting to overwrite in read-only mode...\n");
        strcpy(data, "Overwrite Attempt");
        printf("Unexpected: Data was overwritten!\n");
    } else {
        printf("Write operation failed as expected due to read-only mode.\n");
    }

    if (shmdt(data) == -1) {
        perror("shmdt failed");
        return 1;
    }

    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl IPC_RMID failed");
        return 1;
    }

    printf("Shared memory removed successfully.\n");

    return 0;
}


/*Output:
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./30
Writing data to shared memory...
Reading from shared memory: Hello, Shared Memory!
Attempting to overwrite in read-only mode...
Segmentation fault caught! Cannot write to read-only shared memory.
Write operation failed as expected due to read-only mode.
Shared memory removed successfully.
*/
