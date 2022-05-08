#include <cstdio>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>


void sig_handler_usr1(int sig) {
    printf("usr1 handler %d\n", sig);
    if (sig == SIGUSR1) {
        printf("father: my signal\n");
    }
    else { printf("father: not my signal\n"); }
}

int main() {
    int father_pid, status;
    int son_pid1, son_pid2, son_pid3;
    father_pid = getpid();
    printf("sig_father %d is starting\n", father_pid);

    switch (son_pid1 = fork())
    {
        case -1:
            perror("fork");
            exit(1);
        case 0:
            execl("son1", "son1", NULL);
            break;
        default:
            std::cout << "Executed1 "<< son_pid1 << std::endl;
    }

    switch (son_pid2 = fork())
    {
        case -1:
            perror("fork");
            exit(1);
        case 0:
            execl("son2", "son2", NULL);
            break;
        default:
            std::cout << "Executed2 "<< son_pid2 << std::endl;
    }

    switch (son_pid3 = fork())
    {
        case -1:
            perror("fork");
            exit(1);
        case 0:
            execl("son3", "son3", NULL);
            break;
        default:
            std::cout << "Executed3 "<< son_pid3 << std::endl;
    }
    sleep(1);

    kill(son_pid1, SIGUSR1);
    kill(son_pid2, SIGUSR1);
    kill(son_pid3, SIGUSR1);
    sleep(10);
    wait(&status);
    printf("father end\n");
    return 0;
}