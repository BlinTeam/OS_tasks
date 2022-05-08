#include <cstdio>
#include <sys/ipc.h>
#include <cstdlib>
#include <sys/sem.h>
#include <sys/shm.h>

#include "shmem.h"

int main() {

// указатель на тип Message
// в дальнейшем под сообщения будет
// выделена разделяемая память
    Message* msgptr;
// ключ для создания массива семафоров и
// разделяемой памяти
    key_t key;
// дескриптор разделяемой памяти
    int shmid;
// дескриптор массива семафоров
    int semid;

    int lng, n;
    char stop = 'A';
// создаем ключ
    if ((key = ftok("/home/cruelscript/CLionProjects/OS/server.cpp", 'A')) < 0) {
        printf("Can't get key\n");
        exit(1);
    }

// сервер создает разделяемую память
// функция shmget
    if ((shmid = shmget(key, sizeof(Message), PERM | IPC_CREAT)) < 0) {
        printf("Can't create shared mem\n");
        exit(1);
    }
// получаем указатель на область разделяемой памяти
// (функция shmat)
// и сразу преобразуем указатель к типу Message
    if ((msgptr = (Message*) shmat(shmid, 0, 0)) == nullptr) {
        perror(":(");
    }

// сервер создает массив семафоров (2 семафора)
// функция semget
// значение семафора при создании - 0
    if ((semid = semget(key, 2, PERM | IPC_CREAT)) < 0) {
        perror(":((");
        exit(1);
    }

// ждет когда появится клиент и
// поставит семафор в 1
// функция semop
    if (semop(semid, &proc_wait[0], 1) < 0) {
        printf(":(((\n");
        exit(1);
    }
// если исполняется эта часть программы, то
// клиент уже работает.
// пытаемся заблокировать ресурсэ
// если значение семафора 0, то ставим его в 1
// ( выполняется две операции семафора)
    if (semop(semid, &lock[0], 2) == 0) {
        printf(":((((\n");
        exit(1);
    }
// "Захваченный" ресурс - это разделяемая память
// никто не мешает ей пользоваться
// печатаем содержимое поля buf
// из разделяемой памяти
    printf("%s\n", msgptr->buf);

// освобождаем ресурс
// дожидаемся когда значение семафора будет 1
// (а в 1 мы его сами поставили прошлой операцией)
// и устанавливаем его в 0
    if (semop(semid, &unlock[0], 1) == 0) {
        printf(":((((((\n");
        exit(1);
    }

// "отстыкуем" сегмент разделяемой памяти
    if (shmdt(msgptr) < 0) {
        printf(":((((((((");
    }


    return 0;

}