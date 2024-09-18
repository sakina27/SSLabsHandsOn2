


/*
============================================================================
Name : 2.c
Author : Sakina Baranwala
Description : 3. Write a program to set (any one) system resource limit. Use setrlimit system call.
Date: 18th September, 2024
============================================================================
*/


#include <stdio.h>
#include <sys/resource.h>
#include <stdlib.h>

void set_file_limit(rlim_t new_soft_limit) {
    struct rlimit limit_info;

    if (getrlimit(RLIMIT_NOFILE, &limit_info) != 0) {
        perror("Error getting current file limit");
        exit(EXIT_FAILURE);
    }

    printf("Current limits:\n");
    printf("  Soft limit: %ld\n", (long)limit_info.rlim_cur);
    printf("  Hard limit: %ld\n", (long)limit_info.rlim_max);

    limit_info.rlim_cur = new_soft_limit;

    if (setrlimit(RLIMIT_NOFILE, &limit_info) != 0) {
        perror("Error setting file limit");
        exit(EXIT_FAILURE);
    }

    printf("\nUpdated limits:\n");
    printf("  Soft limit: %ld\n", (long)limit_info.rlim_cur);
    printf("  Hard limit: %ld\n", (long)limit_info.rlim_max);
}

int main() {
    rlim_t new_soft_limit = 2048;
    set_file_limit(new_soft_limit);

    return 0;
}


/*Output:
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ gcc 3.c -o 3
sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./3
Current limits:
  Soft limit: 1024
  Hard limit: 1048576

Updated limits:
  Soft limit: 2048
  Hard limit: 1048576
*/
