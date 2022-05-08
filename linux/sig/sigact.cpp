#include <cstdio>
#include <csignal>
#include <unistd.h>
#include <cstdlib>

void sig_handler_SIGUSR(int sig) {
    if ((kill(getpid(), SIGINT)) == -1) {
        printf("Signal send with error!\n");
    }
    else {
        printf("Signal send OK!\n");
    }
}

void sig_handler_SIGINT(int sig) {
    printf("Signal %i is comming\n", sig);

    sleep(60);
}

void set_action_SIGUSR(int sig, struct sigaction* new_action, struct sigaction* old_action) {
    new_action->sa_handler = sig_handler_SIGUSR;
    sigemptyset(&(new_action->sa_mask));
    sigaddset(&(new_action->sa_mask), SIGUSR1);
    new_action->sa_flags = 0;
    if (sigaction(sig, new_action, old_action) < 0) {
        printf("Action is not setted\n");
        exit(0);
    }
    printf("Action is setted\n");
}

void set_action_SIGINT(int sig, struct sigaction* new_action, struct sigaction* old_action) {
    new_action->sa_handler = sig_handler_SIGINT;
    sigemptyset(&(new_action->sa_mask));
    sigaddset(&(new_action->sa_mask), SIGINT);
    new_action->sa_flags = 0;
    if (sigaction(sig, new_action, old_action) < 0) {
        printf("Action is not setted\n");
        exit(0);
    }
    printf("Action is setted\n");
}

void restore_action(int sig, struct sigaction* old_action) {
    if (sigaction(sig, old_action, nullptr) < 0) {
        printf("We can not restore action!\n");
        exit(0);
    }
    printf("We restored action!\n");
}

int main() {
    struct sigaction new_usr1_action, old_usr1_action,
            new_int_action, old_int_action;
    printf("Sigact pid=%i\n", getpid());
    set_action_SIGUSR(SIGUSR1, &new_usr1_action, &old_usr1_action);
    set_action_SIGINT(SIGINT, &new_int_action, &old_int_action);
    sleep(60);
    restore_action(SIGUSR1, &old_usr1_action);
    restore_action(SIGINT, &old_int_action);
    return 0;
}