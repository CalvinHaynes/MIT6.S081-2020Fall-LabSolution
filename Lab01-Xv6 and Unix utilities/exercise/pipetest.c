/*
 * Copyright(c) 2021 Calvin Haynes
 * MIT Licensed
 * Project:MIT 6.S081
 */

//XV6 book上的一个pipe的例子，写下来测试一下

#include<kernel/types.h>
#include "kernel/stat.h"
#include<user/user.h>


//等同于echo hello world | wc 
void pipetest(){
    
    int p[2];
    char *argv[2];

    argv[0] = "wc";
    argv[1] = 0;

    pipe(p);

    if(fork() != 0){

        //父进程中先关闭读端
        //父进程向管道写端写入hello world\n
        //写完关闭写端

        close(p[0]);
        write(p[1],"hello\n",12);
        close(p[1]);
    } else {

        //前两步其实就是将fd=0的file descriptors指向管道读端p[0]指向的File（设置子进程stdin 为 管道读端）
        //由于子进程是父进程fork出来的，所以指向相同的管道，本来管道也是这个作用的
        //作为子进程和父进程通信的中间媒介，一个共同缓冲区，父进程向其中写入，
        //子进程调用wc system call 进行父进程写入管道中东西的word count

        close(0);//release fd=0的 file
        //dup(int fd)
        //dup system call duplicates an existing file descriptor,
        //returning a new one that refers to the same underlying I/O object(fd refer to). 
        
        dup(p[0]);//创建一个 fd（fd=0） refer to the p[0]指向的file

        //关闭管道读写端，因为前两步已经将读端0设置为管道读端了
        close(p[1]);
        close(p[0]);

        exec("wc",argv);//读出管道中内容执行wc system call
    }
}

int main(){

    pipetest();
    exit(0);
}

