/*
============================================================================
Name : 31a.c
Author : Sakina Baranwala
Description : Write a program to create a semaphore and initialize value to the semaphore.
              b. create a counting semaphore
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
    int counting_key = ftok("counting_sem", 66);
    
    int counting_sem = create_semaphore(counting_key);
    initialize_semaphore(counting_sem, 5);  // Counting semaphore initialized to 5
    printf("Counting semaphore created and initialized to 5.\n");

    return 0;
}
/*Output:
 *
 *
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./31b
Counting semaphore created and initialized to 5.
 */
