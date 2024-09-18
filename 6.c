/*
============================================================================
Name : 6.c
Author : Sakina Baranwala
Description : Write a simple program to create three threads.
Date: 19th September, 2024
============================================================================
*/








#include <stdio.h>
#include <pthread.h>

void* thread_function(void* arg) {
    int thread_num = *((int*)arg);
    printf("Hello from thread %d\n", thread_num);
    return NULL;
}

int main() {
    pthread_t threads[3];
    int thread_args[3];
    int i;

    // Create three threads
    for (i = 0; i < 3; i++) {
        thread_args[i] = i + 1; // Assign thread number
        if (pthread_create(&threads[i], NULL, thread_function, &thread_args[i]) != 0) {
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

    printf("All threads have completed.\n");

    return 0;
}


/*Output:
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./6
Hello from thread 1
Hello from thread 2
Hello from thread 3
All threads have completed.
*/
