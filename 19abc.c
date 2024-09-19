/*
============================================================================
Name : 19abc.c
Author : Sakina Baranwala
Description : Create a FIFO file by
a. mknod command
b. mkfifo command
c. use strace command to find out, which command (mknod or mkfifo) is better.
Date: 19th September, 2024
============================================================================
*/


/*OUTPUT:
 *
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ mkfifo myfifo1
sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ mknod myfifo2 p
sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ strace mknod myfifo1 p

sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ strace mkfifo myfifo2
*/
