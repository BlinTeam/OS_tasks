#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<cstdlib>


int main(){

	int pid,ppid,status;
	pid=getpid();
	ppid=getppid();
	
	printf("\n\n FATHER PARAM: pid=%i ppid=%i\n",pid,ppid);

	if (fork()==0) execl("son3","son3",NULL);
	system ("ps -xf");
	//wait(&status);
}

