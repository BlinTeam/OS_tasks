#include <cstdio>
#include <csignal>
#include <unistd.h>
#include <iostream>

void sig_handler_usr3(int sig) {
    std::cout << "SIGNAL RECEIVED, doc" << std::endl;
}

int main() {
    int son_pid = getpid();
    printf("sig_son %d is starting\n", son_pid);
    signal(SIGUSR1, sig_handler_usr3);
    while(true)
    {
        sleep(4);
        std::cout << "When i will die? (C) son3\n";
    };
}