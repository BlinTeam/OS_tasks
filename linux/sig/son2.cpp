#include <cstdio>
#include <csignal>
#include <unistd.h>
#include <iostream>

int main() {
    int son_pid = getpid();
    printf("sig_son %d is starting\n", son_pid);
    signal(SIGUSR1, SIG_IGN);
    while(true)
    {
        sleep(4);
        std::cout << "When i will die? (C) son2\n";
    };
}