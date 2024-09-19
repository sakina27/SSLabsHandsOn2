/*
============================================================================
Name : 27b.c
Author : Sakina Baranwala
Description : Write a program to receive messages from the message queue.
b. with IPC_NOWAIT as a flag
Date: 20th September, 2024
============================================================================
*/





#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MSG_SIZE 100

struct msgbuf {
    long mtype;
    char mtext[MSG_SIZE];
};

int main() {
    key_t key = ftok("progfile", 65);
    if (key == -1) {
        perror("ftok failed");
        exit(EXIT_FAILURE);
    }

    int msgid = msgget(key, 0666);
    if (msgid == -1) {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }

    struct msgbuf message;
    if (msgrcv(msgid, &message, sizeof(message.mtext), 1, IPC_NOWAIT) == -1) {
        perror("msgrcv failed or no message available");
        exit(EXIT_FAILURE);
    }

    printf("Received Message: %s\n", message.mtext);

    return 0;
}
/*Output:
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./27b
msgrcv failed or no message available: No message of desired type
sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./26
Message sent to queue.
sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./27b
Received Message: Hello, this is a test message.
sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$
*/
