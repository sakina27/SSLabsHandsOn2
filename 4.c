/*
============================================================================
Name : 4.c
Author : Sakina Baranwala
Description : Write a program to measure how much time is taken to execute 100 getppid ( )
system call. Use time stamp counter.
Date: 19th September, 2024
============================================================================
*/




#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

uint64_t read_tsc() {
    unsigned int low, high;
    __asm__ volatile ("rdtsc" : "=a" (low), "=d" (high));
    return ((uint64_t)high << 32) | low;
}

int main() {
    uint64_t start, end;
    int i;

    start = read_tsc();
    
    for (i = 0; i < 100; i++) {
        getppid();
    }
    
    end = read_tsc();

    printf("Cycles taken for 100 getppid() calls: %lu\n", end - start);

    return 0;
}


/*Output:
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ gcc 4.c -o 4
sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./4
Cycles taken for 100 getppid() calls: 75916
*/
