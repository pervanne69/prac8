/* ----------------------------------------------------*/
/* ИМЯ: Pogosian Samvel, ID пользователя: 23К0180      */
/* ДАТА: 02/10/2025                                    */
/* НАЗНАЧЕНИЕ ПРОГРАММЫ:                               */
/* Демонстрация двунаправленного обмена сообщениями    */
/* между родительским и дочерним процессами с помощью  */
/* двух каналов (pipe).                                */
/* Родитель посылает сообщение дочернему процессу,     */
/* получает от него ответ и выводит оба сообщения на   */
/* экран.                                              */
/* ИМЯ ФАЙЛА: pipe_twoway.c                            */
/* ----------------------------------------------------*/
/* ФУНКЦИИ:                                            */
/* main() – создаёт два канала: один для передачи      */
/*          данных от родителя к дочернему процессу,   */
/*          другой — от дочернего к родителю.          */
/*          После fork() каждый процесс закрывает      */
/*          неиспользуемые дескрипторы, обменивается   */
/*          сообщениями и выводит их на экран.         */
/* ----------------------------------------------------*/


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>


int main(void) {
    int parent_to_child[2];
    int child_to_parent[2];

    pid_t pid;

    char buffer[100];

    pipe(parent_to_child);
    pipe(child_to_parent);
    pid = fork();


    if (pid == 0) {
        close(parent_to_child[1]);
        close(child_to_parent[0]);


        read(parent_to_child[0], buffer, sizeof(buffer));
        printf("[child] Got the message: %s\n", buffer);
       
        char reply[] = "Greeting to the parent process";
        write(child_to_parent[1], reply, strlen(reply) + 1);
        
        close(parent_to_child[0]);
        close(child_to_parent[1]);

    } else {
        close(parent_to_child[0]);
        close(child_to_parent[1]);
        
        char msg[] = "Signal from parent process";
        write(parent_to_child[1], msg, strlen(msg) + 1);
        printf("[parent] The message was sent to child process\n");        
        read(child_to_parent[0], buffer, sizeof(buffer));
        printf("[parent] Got the message: %s\n", buffer);
      
        
        close(parent_to_child[1]);
        close(child_to_parent[0]);

    }


    return 0;
}
