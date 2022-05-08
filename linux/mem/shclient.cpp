#include <cstdio>
#include <sys/types.h>
#include <sys/ipc.h>
#include <cstdlib>
#include <sys/sem.h>
#include <sys/shm.h>

#include <cstring>

#include "shmem.h"

int main(){

// указатель на тип Message
// в дальнейшем под сообщения будет 
// выделена разделяемая память
    Message *msgptr;
// ключ для создания массива семафоров и 
// разделяемой памяти
    key_t key;
// дескриптор разделяемой памяти
    int shmid;
// дескриптор массива семафоров
    int semid;
    char buf[100];
    int lng, n;
    char stop='A';

// создаем ключ
    if ( ( key = ftok("/home/cruelscript/CLionProjects/OS/server.cpp",'A' ) ) < 0){
        printf("Can't get key\n");
        exit(1);
    }

// сервер уже создал разделяемую память 
// получаем к ней доступ
    if( ( shmid =shmget( key, sizeof(Message), 0 ) ) < 0 ){
        printf("Can't create shared mem\n");
        exit(1);
    }

// получаем указатель на область разделяемой памяти
// (функция shmat)
// и сразу преобразуем указатель к типу Message
    if ( ( msgptr = ( Message* ) shmat( shmid, 0, 0 ) ) == nullptr ){
        perror(":(");
    }

// сервер уже созда массив семафоров
// поучаем его дескриптор 
    if ( ( semid = semget( key, 2, PERM ) ) < 0 ){
        perror(":(");
        exit(1);
    }
// "Захватываем" ресурс:
// дожидаемся пока семафор станет 0 и выставляемего в 1.
    if ( semop( semid, &lock[0], 2) < 0 ){
        printf(":(\n");
        exit(1);
    }
// Сообщаем сереверу, что клиент работает
// семафор номер 1 устанавливаем в 1.
    if ( semop( semid, &proc_start[0], 1 ) < 0 ){
        printf(":(\n");
        exit(1);
    }

// можем использовать разделяемую память 
// получим строку и запишем ее в разделяемуюю память
    scanf( "%s", buf );

    sprintf( msgptr->buf, "%s", buf );

// освобождаем ресурс
// семафор ставим в 1

    if ( semop ( semid, &unlock[0], 1 ) < 0 ){
        printf(":(\n");
        exit(1);
    }

// заболкируем ресурс, чтобы спокойно их удалить
    if ( semop ( semid, &lock[0], 2 ) < 0 ){
        printf(":(\n");
        exit(1);
    }
// отсоединяем разделяемую память
    if ( shmdt( msgptr ) < 0){
        printf(":(");
    }
// удаляем разделяемую память
    if ( shmctl( shmid, IPC_RMID, 0 ) < 0 ){
        printf(":(\n");
    }
// удаляем массив семафоров
    if ( semctl( semid, 2, IPC_RMID ) < 0 ){
        printf(":(\n");
    }

    return 0;
}