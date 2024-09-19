/*
============================================================================
Name : 25.c
Author : Sakina Baranwala
Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
a. access permission
b. uid, gid
c. time of last message sent and received
d. time of last change in the message queue
d. size of the queue
f. number of messages in the queue
g. maximum number of bytes allowed
h. pid of the msgsnd and msgrcv
Date: 20th September, 2024
============================================================================
*/


#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int key = ftok("progfile", 65);
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    int msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    struct msqid_ds buf;
    if (msgctl(msgid, IPC_STAT, &buf) == -1) {
        perror("msgctl failed");
        exit(1);
    }

    printf("Access Permissions: %o\n", buf.msg_perm.mode);
    printf("UID: %d\n", buf.msg_perm.uid);
    printf("GID: %d\n", buf.msg_perm.gid);
    printf("Time of Last Message Sent: %s", ctime(&buf.msg_stime));
    printf("Time of Last Message Received: %s", ctime(&buf.msg_rtime));
    printf("Time of Last Change: %s", ctime(&buf.msg_ctime));
    printf("Size of Queue (bytes): %lu\n", buf.__msg_cbytes);
    printf("Number of Messages in Queue: %lu\n", buf.msg_qnum);
    printf("Maximum Number of Bytes Allowed: %lu\n", buf.msg_qbytes);
    printf("PID of Last msgsnd: %d\n", buf.msg_lspid);
    printf("PID of Last msgrcv: %d\n", buf.msg_lrpid);

    return 0;
}


/*Output:
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./25
Access Permissions: 666
UID: 1000
GID: 1000
Time of Last Message Sent: Thu Jan  1 05:30:00 1970
Time of Last Message Received: Thu Jan  1 05:30:00 1970
Time of Last Change: Fri Sep 20 01:15:26 2024
Size of Queue (bytes): 0
Number of Messages in Queue: 0
Maximum Number of Bytes Allowed: 16384
PID of Last msgsnd: 0
PID of Last msgrcv: 0
*/
