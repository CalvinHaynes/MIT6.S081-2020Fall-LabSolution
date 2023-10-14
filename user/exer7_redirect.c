// redirect: 运行一个命令使得输出重定向了

#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main(){
    int pid;

    pid = fork();

    if(pid == 0){
        close(1);
        open("output.txt", O_WRONLY|O_CREATE);

        char *argv[] = { "echo", "THIS", "IS", "A", "FUCKING", "REDIRECT", "ECHO", 0};
        exec("echo", argv);
        printf("exec failed!\n");
        exit(1);
    } else{
        wait((int *)0);
    }

    exit(0);
}