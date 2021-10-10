// create a new process

#include "kernel/types.h"
#include "user/user.h"

int main(){
    int pid;

    pid = fork();

    printf("fork() returned %d\n",pid);

    if(pid == 0){
        printf("child process\n");
    } else{
        printf("parent process\n");
    }

    exit(0);
}