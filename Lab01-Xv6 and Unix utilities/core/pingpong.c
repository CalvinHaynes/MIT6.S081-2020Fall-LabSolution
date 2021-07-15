/*
 * Copyright(c) 2021 Calvin Haynes
 * MIT Licensed
 * Project:MIT 6.S081
 */


//pingpong.c(easy)

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