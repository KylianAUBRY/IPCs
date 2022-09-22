#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

// fonction de traitement du signal SIGUSR1

void traitement(int sig) {
    (void) signal(SIGUSR1, traitement);
    printf("un signal SIGUSR1 ppid :%d\n", getppid());
}

int main(int argc, char *argv[]) {
    int pid, pidP1, pidP2;
    (void) signal(SIGUSR1, traitement);
    pidP1 = getpid();
    pid = fork();

    if (pid == -1) {
        printf("pb creation fork : %s\n", strerror(errno));
        exit(1);
    } else {
        if (pid == 0) {
            pid = fork();
            if (pid == 0) {//P2
                pidP2 = getppid();
                printf("p3 pid=%d\n", getpid());
                kill(pidP2, SIGUSR1);
                sleep(2);
            } else {
                printf("p2 pid=%d\n", getpid());
                pause();
                pause();
            }
        }
        else {
            printf("pere pid=%d\n", getpid());
            sleep(1);
            kill(pid, SIGUSR1);
            sleep(1);
        }
    }

    return EXIT_SUCCESS;
}