/*
============================================================================
Name : 26.c
Author : Sakina Baranwala
Description : Write a program to send messages to the message queue. Check $ipcs -q
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

    int msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }

    struct msgbuf message;
    message.mtype = 1;  // Message type
    strncpy(message.mtext, "Hello, this is a test message.", MSG_SIZE);

    if (msgsnd(msgid, &message, sizeof(message.mtext), 0) == -1) {
        perror("msgsnd failed");
        exit(EXIT_FAILURE);
    }

    printf("Message sent to queue.\n");

    return 0;
}



/*Output:
 *
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./26
Message sent to queue.
sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages
0xffffffff 0          sakina     666        0            0
0x410449c6 1          sakina     666        100          1  */
