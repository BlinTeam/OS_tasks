#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <cstdio>
#include <unistd.h>

#define FIFO1 "/tmp/fifo1"
#define FIFO2 "/tmp/fifo2"

#define MAXLINE 256

int server(int readfd, int writefd);

int main(int args, char **argv) {
    int readfd, writefd;

    if ((mkfifo(FIFO1, 0777)) < 0) {
        perror("mkfifo");
        return 1;
    }
    printf("Server: %s is created\n", FIFO1);

    if ((mkfifo(FIFO2, 0777)) < 0) {
        perror("mkfifo");
        return 1;
    }
    printf("Server: %s is created\n", FIFO2);

    if ((readfd = open(FIFO1, O_RDONLY)) <= 0) {
        perror("openfifo");
        return 1;
    }
    printf("Server: %s is opened for read and readfd=%d\n", FIFO1, readfd);

    if ((writefd = open(FIFO2, O_WRONLY)) <= 0) {
        perror("openfifo");
        return 1;
    }
    printf("Server: %s is opened for write and writefd=%d\n", FIFO2, writefd);

    server(readfd, writefd);
    return 0;
}

int server(int readfd, int writefd) {
    char buf[MAXLINE];
    int i, n, fd;
    // FILE* fd;

    printf("Server: readfd=%d writefd=%d\n", readfd, writefd);
    memset(buf, '\0', MAXLINE);

    while ((n = read(readfd, buf, MAXLINE - 1)) < 0) {
        perror("read");
        return 1;
    }
    buf[n] = '\0';
    printf("Server: file name=%s len=%d\n", buf, n);
    //strcpy(buf,"mkfifo.c");
    //n=strlen(buf);
    for (i = 0; i < n; i++)
        printf("%d %c\n", i, buf[i]);

    if ((fd = open(buf, O_RDONLY)) < 0) {
        perror("open");
        return 1;
    }
    //if((fd=fopen("mkfifo.c","rt"))==NULL){ perror("open"); return 1;}
    printf("Server: file %s is opened\n", buf);
    while ((n = read(fd, buf, MAXLINE - 1)) > 0)
        write(writefd, buf, n);

    close(readfd);
    return 0;

}