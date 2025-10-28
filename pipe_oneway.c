#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(void) {
    int fd[2];
    pid_t pid;

    char msg[] = "Message from parent process";
    char buffer[100];

    pipe(fd);
    pid = fork();


    if (pid == 0) {
        close(fd[1]);
        read(fd[0], buffer, sizeof(buffer));
        printf("[child] Got the message: %s\n", buffer);
        close(fd[0]);
    } else {
        close(fd[0]);
        write(fd[1], msg, strlen(msg) + 1);
        printf("[parent] The message was sent to child process\n");
        close(fd[1]);
    }

    return 0;
}
