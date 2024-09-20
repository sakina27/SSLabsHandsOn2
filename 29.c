/*
============================================================================
Name : 29.c
Author : Sakina Baranwala
Description : Write a program to remove the message queue.
Date: 20th September, 2024
============================================================================
*/






#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

int main() {
    int key;
    int msgid;

    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        return 1;
    }

    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl IPC_RMID failed");
        return 1;
    }

    printf("Message queue removed successfully.\n");

    return 0;
}


/*Output:
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./29
Message queue removed successfully.
*/
