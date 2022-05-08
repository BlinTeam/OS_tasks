#include <cstdio>
#include <unistd.h>
#include <csignal>

void handler(int sig) {
    switch (sig) {
        case SIGINT:
            printf("catching SIGINT\n");
            break;
        case SIGTSTP:
            printf("catching SIGTCTP\n");
            break;
        case SIGQUIT:
            printf("catching SIGQUIT\n");
            break;
        default:
            printf("catching sig=%d\n", sig);
            break;
    }
}

int main() {
    int main_pid, status;
    main_pid = getpid();
    printf("main %d is starting\n", main_pid);

    if (signal(SIGINT, handler) == SIG_ERR) perror("signal SIGINT");
    if (signal(SIGTSTP, handler) == SIG_ERR) perror("signal SIGTSTP");
    if (signal(SIGQUIT, handler) == SIG_ERR) perror("signal SIGQUIT");
    if (signal(SIGUSR1, handler) == SIG_ERR) perror("signal SIGUSR1");

    while(true) {
        printf("main is running\n");
        sleep(100);
    }

    printf("main end\n");
    return 0;
}