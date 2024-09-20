/*
============================================================================
Name : 32.c
Author : Sakina Baranwala
Description : Write a program to implement semaphore to protect any critical section.
              a. rewrite the ticket number creation program using semaphore
              b. protect shared memory from concurrent write access
              c. protect multiple pseudo resources ( may be two) using counting semaphore
              d. remove the created semaphore
Date: 20th September, 2024
============================================================================
*/







#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

int semaphore_id;
int *ticket_number = 0;

void wait_semaphore() {
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = -1;
    sb.sem_flg = 0;
    semop(semaphore_id, &sb, 1);
}

void signal_semaphore() {
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = 1;
    sb.sem_flg = 0;
    semop(semaphore_id, &sb, 1);
}

void create_ticket() {
    wait_semaphore();
    printf("Ticket created: %d\n", ++(*ticket_number));
    sleep(1);
    signal_semaphore();
}

void shared_memory_access() {
    int shm_key = ftok("shmfile", 65);
    int shm_id = shmget(shm_key, 1024, 0666 | IPC_CREAT);
    char *shared_memory = (char *)shmat(shm_id, NULL, 0);

    if (fork() == 0) {
        wait_semaphore();
        strcpy(shared_memory, "Child process wrote to shared memory.\n");
        printf("Child wrote to shared memory.\n");
        signal_semaphore();
        shmdt(shared_memory);
        exit(0);
    } else {
        wait(NULL);
        wait_semaphore();
        printf("Parent reads: %s", shared_memory);
        signal_semaphore();
        shmdt(shared_memory);
        shmctl(shm_id, IPC_RMID, NULL);
    }
}

void access_resource(int resource_id) {
    wait_semaphore();
    printf("Process %d accessing resource %d\n", getpid(), resource_id);
    sleep(1);
    printf("Process %d releasing resource %d\n", getpid(), resource_id);
    signal_semaphore();
}

void manage_pseudo_resources() {
    for (int i = 0; i < 4; i++) {
        if (fork() == 0) {
            access_resource(i % 2);
            exit(0);
        }
    }
    for (int i = 0; i < 4; i++) {
        wait(NULL);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s [ticket|shared|resource]\n", argv[0]);
        exit(1);
    }

    int sem_key = ftok("semfile", 65);
    semaphore_id = semget(sem_key, 1, 0666 | IPC_CREAT);
    
    if (strcmp(argv[1], "ticket") == 0) {
        semctl(semaphore_id, 0, SETVAL, 1);
        int shm_key = ftok("ticket_shm", 65);
        int shm_id = shmget(shm_key, sizeof(int), 0666 | IPC_CREAT);
        ticket_number = (int *)shmat(shm_id, NULL, 0);
        *ticket_number = 0;

        for (int i = 0; i < 5; i++) {
            if (fork() == 0) {
                create_ticket();
                exit(0);
            }
        }
        for (int i = 0; i < 5; i++) {
            wait(NULL);
        }

        shmdt(ticket_number);
        shmctl(shm_id, IPC_RMID, NULL);

    } else if (strcmp(argv[1], "shared") == 0) {
        semctl(semaphore_id, 0, SETVAL, 1);
        shared_memory_access();

    } else if (strcmp(argv[1], "resource") == 0) {
        semctl(semaphore_id, 0, SETVAL, 2);
        manage_pseudo_resources();
    } else {
        printf("Invalid argument. Use 'ticket', 'shared', or 'resource'.\n");
    }

    semctl(semaphore_id, 0, IPC_RMID);
    return 0;
}


/*Output:
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./32 ticket
Ticket created: 1
Ticket created: 2
Ticket created: 3
Ticket created: 4
Ticket created: 5
sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./32 shared
Child wrote to shared memory.
Parent reads: Child process wrote to shared memory.
sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./32 resource
Process 7037 accessing resource 0
Process 7038 accessing resource 1
Process 7037 releasing resource 0
Process 7038 releasing resource 1
Process 7040 accessing resource 1
Process 7039 accessing resource 0
Process 7040 releasing resource 1
Process 7039 releasing resource 0
*/
