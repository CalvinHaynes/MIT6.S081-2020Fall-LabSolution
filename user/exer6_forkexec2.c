// fork then exec
// 先fork一个子进程,然后在子进程中执行exec

#include "kernel/types.h"
#include "user/user.h"

int main(){
    int pid, status;

    pid = fork();

    if(pid == 0){
        char *argv[] = { "echo", "THIS", "IS", "ECHO", 0};
        exec("afuckingshitecho", argv);
        printf("exec failed!\n");
        //指令afuckingshitecho不存在,exit(1)将1传递给父进程
        exit(1);
    } else{
        printf("parent waiting\n");
        //wait将status值(1)写入
        wait(&status);
        printf("the child exited with status %d\n",status);
    }

    exit(0);
}