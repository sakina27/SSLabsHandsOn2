

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
        pause();
    }

    return 0;
}

