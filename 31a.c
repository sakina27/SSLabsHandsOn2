/*
============================================================================
Name : 31a.c
Author : Sakina Baranwala
Description : Write a program to create a semaphore and initialize value to the semaphore.
a. create a binary semaphore
Date: 20th September, 2024
============================================================================
*/





#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>

void initialize_semaphore(int semid, int value) {
    if (semctl(semid, 0, SETVAL, value) == -1) {
        perror("semctl failed");
        exit(1);
    }
}

int create_semaphore(int key) {
    int semid = semget(key, 1, 0666 | IPC_CREAT);
    if (semid == -1) {
        perror("semget failed");
        exit(1);
    }
    return semid;
}

int main() {
    int binary_key = ftok("binary_sem", 65);
    
    int binary_sem = create_semaphore(binary_key);
    initialize_semaphore(binary_sem, 1);  // Binary semaphore initialized to 1
    printf("Binary semaphore created and initialized to 1.\n");

    return 0;
}


/*Output:
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./30a
Binary semaphore created and initialized to 1.
*/
