#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

int main() {

    key_t key;

    int id;

    if ((key = ftok(".", 'J')) == -1) {
        perror("ftok");
        exit(1);
    }

    if ((id = semget(key, 1, 0)) == -1) {
        perror("semget");
        exit(1);
    }

    int count = 0;
    while (true) {
        if ((count = semctl(id, 0, GETNCNT)) == -1) {
            perror("semctl");
            exit(1);
        }
        printf("Number of waiting processes: %d\n", count);
        sleep(3);
    }
    return 0;
}
