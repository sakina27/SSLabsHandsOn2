/*
============================================================================
Name : 1a.c
Author : Sakina Baranwala
Description : Write a separate program (for each time domain) to set a interval timer in 10sec and
              10micro second
              a. ITIMER_REAL
Date: 17th September, 2024
============================================================================
*/





#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void alarm_handler(int signum) {
    printf("Real-time interval timer expired.\n");
}

int main() {
    struct itimerval timer_config;
    signal(SIGALRM, alarm_handler);
    timer_config.it_value.tv_sec = 10;
    timer_config.it_value.tv_usec = 0;
    timer_config.it_interval.tv_sec = 0;
    timer_config.it_interval.tv_usec = 10;

    if (setitimer(ITIMER_REAL, &timer_config, NULL) == -1) {
        perror("Failed to set ITIMER_REAL");
        return 1;
    }

    while (1) {
    }

    return 0;
}


/*Output:
 * sakina@sakina-VivoBook-ASUSLaptop-X515EA-X515EA:~/handsOn2$ ./1a

  //After 10 seconds
  Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
Real-time interval timer expired.
//Until we pause it
*/
