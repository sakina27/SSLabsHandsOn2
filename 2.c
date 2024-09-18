/*
============================================================================
Name : 2.c
Author : Sakina Baranwala
Description : 2. Write a program to print the system resource limits. Use getrlimit system call.
Date: 18th September, 2024
============================================================================
*/





#include <stdio.h>
#include <sys/resource.h>
#include <stdlib.h>

void display_limit(int resource, const char *resource_name) {
    struct rlimit limit_info;

    if (getrlimit(resource, &limit_info) != 0) {
        perror("Error getting resource limit");
        exit(EXIT_FAILURE);
    }

    printf("%s:\n", resource_name);
    printf("  Soft limit: %ld\n", (long)limit_info.rlim_cur);
    printf("  Hard limit: %ld\n\n", (long)limit_info.rlim_max);
}

int main() {
    display_limit(RLIMIT_CPU, "CPU time limit (in seconds)");
    display_limit(RLIMIT_FSIZE, "Maximum file size (in bytes)");
    display_limit(RLIMIT_DATA, "Data segment size (in bytes)");
    display_limit(RLIMIT_STACK, "Stack size (in bytes)");
    display_limit(RLIMIT_CORE, "Core dump size (in bytes)");
    display_limit(RLIMIT_RSS, "Resident set size (in bytes)");
    display_limit(RLIMIT_NOFILE, "Maximum number of open files");
    display_limit(RLIMIT_AS, "Address space size (in bytes)");
    display_limit(RLIMIT_NPROC, "Maximum number of processes");
    display_limit(RLIMIT_MEMLOCK, "Locked-in-memory size (in bytes)");
    display_limit(RLIMIT_LOCKS, "Maximum number of file locks");
    
    return 0;
}



/*Output:
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ gcc 2.c -o 2
sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./2
CPU time limit (in seconds):
  Soft limit: -1
  Hard limit: -1

Maximum file size (in bytes):
  Soft limit: -1
  Hard limit: -1

Data segment size (in bytes):
  Soft limit: -1
  Hard limit: -1

Stack size (in bytes):
  Soft limit: 8388608
  Hard limit: -1

Core dump size (in bytes):
  Soft limit: 0
  Hard limit: -1

Resident set size (in bytes):
  Soft limit: -1
  Hard limit: -1

Maximum number of open files:
  Soft limit: 1024
  Hard limit: 1048576

Address space size (in bytes):
  Soft limit: -1
  Hard limit: -1

Maximum number of processes:
  Soft limit: 62429
  Hard limit: 62429

Locked-in-memory size (in bytes):
  Soft limit: 2055282688
  Hard limit: 2055282688

Maximum number of file locks:
  Soft limit: -1
  Hard limit: -1
*/

