/*
============================================================================
Name : 28.c
Author : Sakina Baranwala
Description : Write a program to change the exiting message queue permission. (use msqid_ds structure)
Date: 20th September, 2024
============================================================================
*/







#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <errno.h>

int main() {
    int key;
    int msgid;
    struct msqid_ds msgq_ds;

    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        return 1;
    }

    if (msgctl(msgid, IPC_STAT, &msgq_ds) == -1) {
        perror("msgctl IPC_STAT failed");
        return 1;
    }

    printf("Current Permissions: %o\n", msgq_ds.msg_perm.mode);

    msgq_ds.msg_perm.mode = 0444;

    if (msgctl(msgid, IPC_SET, &msgq_ds) == -1) {
        perror("msgctl IPC_SET failed");
        return 1;
    }

    printf("Updated Permissions: %o\n", msgq_ds.msg_perm.mode);

    return 0;
}


/*Output:
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./28
Current Permissions: 666
Updated Permissions: 444
sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$*/
