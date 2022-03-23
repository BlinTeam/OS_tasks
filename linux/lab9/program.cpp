#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1023

int main () {
	pid_t pid;

	int id1, id2, id3;
	char c, *shm1, *shm2, *shm3, *s;

	if ((id1=shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT|0666)) < 0) {
		perror("shmget failed");
		exit(1);
	}

	if ((id2=shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT|0666)) < 0){
		perror("shmget failed");
		exit(1);
	}

	if ((id3=shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT|0666)) < 0){
		perror("shmget failed");
		exit(1);
	}

	if ((shm1 = (char*) shmat(id1, 0, 0)) == (char*)-1){
		perror("shmat failed!");
		exit(2);
	}

	if ((shm2 = (char*) shmat(id2, 0, 0)) == (char*)-1) {
		perror("shmat failed!");
		exit(2);
	}

	if ((shm3 = (char*) shmat(id3, 0, 0)) == (char*)-1) {
		perror("shmat failed!");
		exit(2);
	}

	printf("shm1: %10p\n", shm1);
	printf("shm2: %10p\n", shm2);
	printf("shm3: %10p\n", shm3);

	*(shm1 + SHM_SIZE) = 'a';
	*(shm2 + SHM_SIZE) = 'b';
	*(shm3 + SHM_SIZE) = 'c';

	printf("1024th byte = %c\n", *(shm1 + SHM_SIZE));
	printf("1024th byte = %c\n", *(shm2 + SHM_SIZE));
	printf("1024th byte = %c\n", *(shm3 + SHM_SIZE));

	shmctl(id1, IPC_RMID, (struct shmid_ds *) 0 );
	shmctl(id2, IPC_RMID, (struct shmid_ds *) 0 );
	shmctl(id3, IPC_RMID, (struct shmid_ds *) 0 );
}

