/*
============================================================================
Name : 1c.c
Author : Sakina Baranwala
Description : WWrite a separate program (for each time domain) to set a interval timer in 10sec and
10micro second
c. ITIMER_PROF
Date: 19th September, 2024
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handle_prof_timer(int sig) {
    printf("Profiling timer expired.\n");
}

int main() {
    struct itimerval timer;

    if (signal(SIGPROF, handle_prof_timer) == SIG_ERR) {
        perror("Signal error");
        return 1;
    }

    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 0;

    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 10;

    if (setitimer(ITIMER_PROF, &timer, NULL) == -1) {
        perror("Failed to set ITIMER_PROF");
        return 1;
    }

    while (1) {
    }

    return 0;
}


/*Output:
 *
 *
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./1c
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
Profiling timer expired.
*/
