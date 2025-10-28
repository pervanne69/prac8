/* ----------------------------------------------------*/
/* ИМЯ: Pogosian Samvel, ID пользователя: 23К0180      */
/* ДАТА: 02/10/2025                                    */
/* НАЗНАЧЕНИЕ ПРОГРАММЫ:                               */
/* Демонстрация однонаправленного обмена данными       */
/* между процессами с использованием канала (pipe).    */
/* Родительский процесс записывает сообщение в pipe,   */
/* а дочерний процесс считывает его и выводит на экран.*/
/* ИМЯ ФАЙЛА: pipe_oneway.c                            */
/* ----------------------------------------------------*/
/* ФУНКЦИИ:                                            */
/* main() – создаёт канал и порождает дочерний процесс;*/
/*          если процесс — дочерний, он читает данные  */
/*          из pipe и выводит сообщение;               */
/*          если процесс — родительский, он записывает */
/*          строку в pipe и завершает работу.          */
/* ----------------------------------------------------*/


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
