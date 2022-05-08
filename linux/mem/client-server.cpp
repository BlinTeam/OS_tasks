#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <sys/fcntl.h>
#include <cstring>
#include <sys/wait.h>

std::string error = "Can't find file with this name";
#define MAXLINE 100000

void client(int readfd, int writefd) {
    size_t len;
    ssize_t n;
    char buff[MAXLINE];
    fgets(buff, MAXLINE, stdin);
    len = strlen(buff);
    if (buff[len - 1] == '\n')
        len--;
    write(writefd, buff, len);
    while ((n = read(readfd, buff, MAXLINE)) < 1) {}
    std::cout << buff;
}

void server(int readfd, int writefd) {
    int fd;
    ssize_t n;
    char buff[MAXLINE + 1];
    if ((n = read(readfd, buff, MAXLINE)) == 0)
    buff[n] = '\0';

    if ((fd = open(buff, O_RDONLY)) < 0) {
        strcpy(buff, error.c_str());
        ssize_t size1 = strlen(error.c_str());
        write(writefd, buff, size1 + 1);
        close(fd);
    } else {
        while ((n = read(fd, buff, MAXLINE)) > 0) {
            write(writefd, buff, n);
        }
        close(fd);
    }
}

int main(int argc, char **argv) {
    int pipe1[2], pipe2[2];
    pid_t childpid;
    pipe(pipe1);
    pipe(pipe2);
    if ((childpid = fork()) == 0) {// child
        close(pipe1[1]);
        close(pipe2[0]);
        server(pipe1[0], pipe2[1]);
        exit(0);
    }
// parent close(pipe1[0]); close(pipe2[1]);
    client(pipe2[0], pipe1[1]);
    waitpid(childpid, NULL, 0);
    exit(0);
}