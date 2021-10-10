// repalce a process with a executable file
// 用一个新的可执行文件替换当前进程

#include "kernel/types.h"
#include "user/user.h"

int main(){
    char *argv[] = { "echo", "this", "is", "echo", 0};
    
    exec("echo", argv);

    printf("exec failed!");

    exit(0);
}