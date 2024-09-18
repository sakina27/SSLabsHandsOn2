
/*
============================================================================
Name : 7.c
Author : Sakina Baranwala
Description : Write a simple program to print the created thread ids.
Date: 19th September, 2024
============================================================================
*/






#include <stdio.h>
#include <pthread.h>

void* thread_function(void* arg) {
    pthread_t thread_id = pthread_self();
    printf("Thread ID: %lu\n", (unsigned long)thread_id);
    return NULL;
}

int main() {
    pthread_t threads[3];
    int i;

    // Create three threads
    for (i = 0; i < 3; i++) {
        if (pthread_create(&threads[i], NULL, thread_function, NULL) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Wait for all threads to complete
    for (i = 0; i < 3; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            return 1;
        }
    }

    return 0;
}



/*Output:
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./7
Thread ID: 139900923934400
Thread ID: 139900915541696
Thread ID: 139900907148992
*/
