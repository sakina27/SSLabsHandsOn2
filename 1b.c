/*
============================================================================
Name : 1b.c
Author : Sakina Baranwala
Description : Write a separate program (for each time domain) to set a interval timer in 10sec and
              10micro second
              b. ITIMER_VIRTUAL 
Date: 17th September, 2024
============================================================================
*/




#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void virtual_timer_handler(int signum) {
    printf("Virtual time interval timer expired.\n");
}

int main() {
    struct itimerval timer_settings;

    signal(SIGVTALRM, virtual_timer_handler);

    
    timer_settings.it_value.tv_sec = 10;
    timer_settings.it_value.tv_usec = 0;

    
    timer_settings.it_interval.tv_sec = 0;
    timer_settings.it_interval.tv_usec = 10;

    if (setitimer(ITIMER_VIRTUAL, &timer_settings, NULL) == -1) {
        perror("Failed to set ITIMER_VIRTUAL");
        return 1;
    }

    
    while (1) {
        for (volatile int i = 0; i < 1000000; ++i);

         usleep(10000); 
    }

    return 0;
}

/*sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./1b
Virtual time interval timer expired.
Virtual time interval timer expired.
Virtual time interval timer expired.
Virtual time interval timer expired.
Virtual time interval timer expired.
Virtual time interval timer expired.
Virtual time interval timer expired.
Virtual time interval timer expired.
Virtual time interval timer expired.
Virtual time interval timer expired.
Virtual time interval timer expired.
Virtual time interval timer expired.
Virtual time interval timer expired.
Virtual time interval timer expired.
Virtual time interval timer expired.
Virtual time interval timer expired.
Virtual time interval timer expired.
Virtual time interval timer expired.
Virtual time interval timer expired.
Virtual time interval timer expired.
Virtual time interval timer expired.
Virtual time interval timer expired.
Virtual time interval timer expired.
Virtual time interval timer expired.
Virtual time interval timer expired.
Virtual time interval timer expired.
Virtual time interval timer expired.
//Until we pause
*/
