#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <csignal>
#include <iostream>

void signal1(int sig_num) {

    signal(sig_num, signal1);

    std::cout << "Signal" << sig_num << "from parent received.\n";
    if (sig_num == SIGQUIT)
        exit(1);
}

void signal2(int sig_num) {

    signal(sig_num, signal2);

    std::cout << "Signal" << sig_num << "from child received.\n";
    if (sig_num == SIGQUIT)
        exit(1);
}

int main() {
    struct sigaction sa;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    int childPid = fork();
    int parentPid;

    if (fork() == 0) {
        sa.sa_handler = signal1;
        parentPid = getppid();
        if (sigaction(SIGUSR1, &sa, nullptr) == -1) {
            std::cout << "signal from parent not recieved\n";
            perror("SIGQUIT");
            exit(1);
        }
        while (true) {
            sleep(2);
            kill(parentPid, SIGUSR1);
        }

    } else {
        sa.sa_handler = signal2;
        if (sigaction(SIGUSR1, &sa, NULL) == -1) {
            std::cout << "signal from child not| recieved\n";
            perror("SIGINT");
            exit(1);
        }
        while (true) {
            sleep(1);
            kill(childPid, SIGUSR1);
        }
    }
}
