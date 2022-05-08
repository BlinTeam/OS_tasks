#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <cstdio>
#include <unistd.h>

#define FIFO1 "/tmp/fifo1"
#define FIFO2 "/tmp/fifo2"

#define MAXLINE 256

int client(int readfd, int writefd);

int main(int args, char **argv) {
    int writefd, readfd;

    if ((writefd = open(FIFO1, O_WRONLY)) <= 0) {
        perror("openfifo");
        return 1;
    }
    printf("Client: %s is opened for write and writefd=%d\n", FIFO1, writefd);

    if ((readfd = open(FIFO2, O_RDONLY)) <= 0) {
        perror("openfifo");
        return 1;
    }
    printf("Client: %s is opened for read and readfd=%d\n", FIFO2, readfd);

    client(readfd, writefd);

    close(readfd);
    close(writefd);

    if (unlink(FIFO1) < 0) {
        perror("unlink");
        return 1;
    }
    printf("Client: %s is deleted\n", FIFO1);

    if (unlink(FIFO2) < 0) {
        perror("unlink");
        return 1;
    }
    printf("Client: %s is deleted\n", FIFO2);

    printf("Client: end\n");
    return 0;
}

int client(int readfd, int writefd) {
    char buf[MAXLINE];
    int n, fd, len;

    printf("Client: readfd=%d writefd=%d\n", readfd, writefd);
    memset(buf, '\0', MAXLINE);

    printf("Client: File name please\n");
    fgets(buf, MAXLINE, stdin);
    len = strlen(buf);
    if (buf[len - 1] == '\n') len--;
    //strcpy(buf,"mkfifo.c");
    printf("Client: File name %s for Server\n", buf);

    if (write(writefd, buf, len) != len) {
        perror("write");
        return 1;
    }

    while ((n = read(readfd, buf, MAXLINE - 1)) > 0)
        write(1, buf, n);
    return 0;
}