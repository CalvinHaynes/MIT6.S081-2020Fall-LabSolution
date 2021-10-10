// create a file , write to it

#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main(){
    int fd = open("output.txt",O_WRONLY | O_CREATE);
    write(fd,"hahaha\n",7);

    exit(0);
}