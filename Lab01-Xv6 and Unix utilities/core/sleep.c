/*
 * Copyright(c) 2021 Calvin Haynes
 * MIT Licensed
 * Project:MIT 6.S081
 */


// 要求如下：
// Implement the UNIX program sleep for xv6;
// your sleep should pause for a user-specified number of ticks.
// A tick is a notion of time defined by the xv6 kernel,
// namely the time between two interrupts from the timer chip. 
// Your solution should be in the file user/sleep.c.


#include<user/user.h>
#include<kernel/types.h>

int main(int argc,char* argv[]){
    if(argc != 2){
        fprintf(2,"The call of sleep only need an argument!");
        exit(1);
    }

    int sleepTime = atoi(argv[1]);
    printf("(nothing happens for a little while)\n");
    // printf("I am sleeping for a while!＜(▰˘◡˘▰)！\n");

    sleep(sleepTime);
    exit(0);
}

//测试输出如下：
// $ sleep 10
// (nothing happens for a little while)

// root@calvinhaynes-virtual-machine:~/xv6-labs-2020# ./grade-lab-util sleep
// make: “kernel/kernel”已是最新。
// == Test sleep, no arguments == sleep, no arguments: OK (1.5s) 
// == Test sleep, returns == sleep, returns: OK (0.9s) 
// == Test sleep, makes syscall == sleep, makes syscall: OK (0.9s) 