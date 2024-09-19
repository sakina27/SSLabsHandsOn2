/*
============================================================================
Name : 24.c
Author : Sakina Baranwala
Description : Write a program to create a message queue and print the key and message queue id.
Date: 20th September, 2024
============================================================================
*/







#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    key_t key = ftok("progfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    if (msgid == -1) {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }

    printf("Key: %d\n", key);
    printf("Message Queue ID: %d\n", msgid);

    return 0;
}



/*Output:
 *
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./24
Key: 1090800070
Message Queue ID: 1
*/
