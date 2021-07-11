/*
 * Copyright(c) 2021 Calvin Haynes
 * MIT Licensed
 * Project:MIT 6.S081
 */


//pingpong.c(easy)

// 要求如下：
// Write a program that uses UNIX system calls to 
// ''ping-pong'' a byte between two processes over a pair of pipes, 
// one for each direction. The parent should send a byte to the child;
//  the child should print "<pid>: received ping", 
//  where <pid> is its process ID, write the byte on the pipe to the parent, 
//  and exit; the parent should read the byte from the child, 
//  print "<pid>: received pong", and exit. 
//  Your solution should be in the file user/pingpong.c.


#include<kernel/types.h>
#include<user/user.h>


void pingpong(){
    
    char buffer[10];
    int p[2];

    pipe(p);

    if(fork() != 0){
        write(p[1],"ping\n",6);
        close(p[1]);
        wait(0);
        read(p[0],buffer,6);
        printf("%d: received %s",getpid(),buffer);
        close(p[0]);
    }else{
        read(p[0],buffer,6);
        printf("%d: received %s",getpid(),buffer);
        close(p[0]);
        write(p[1],"pong\n",6);
        close(p[1]);
    }
}


int main(){
    pingpong();
    exit(0);
}

//测试输出如下：

// $ pingpong
// 4: received ping
// 3: received pong

// root@calvinhaynes-virtual-machine:~/xv6-labs-2020# ./grade-lab-util pingpong
// make: “kernel/kernel”已是最新。
// == Test pingpong == pingpong: OK (2.1s) 