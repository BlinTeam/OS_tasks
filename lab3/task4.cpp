#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <limits.h>

#include <iostream>

int main(int argc, char* argv[]) {
	int fds[argc-1][2];
	for (int i = 0; i < argc - 1; i++) {
		pipe(fds[i]);
	}
	for (int i = 0; i < argc - 1; i++) {
		if (fork() == 0) {
			if (i > 0) {
				dup2(fds[i-1][0], 0);
				close(fds[i-1][1]);
			} else {
				close(fds[i][0]);
			}
			if (i < argc - 2) {
				dup2(fds[i][1], 1);
			} else {
				close(fds[i][1]);
			}
			for (int j = i + 1; j < argc - 1; j++) {
				close(fds[j][0]);
				close(fds[j][1]);
			}
			execlp(argv[i+1],  argv[i+1], NULL);
		} else {
			if (i > 0) {
				close(fds[i-1][0]);
				close(fds[i-1][1]);
			}
			wait(0);
		}
	}
}

