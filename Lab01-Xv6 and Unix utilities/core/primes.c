/*
 * Copyright(c) 2021 Calvin Haynes
 * MIT Licensed
 * Project:MIT 6.S081
 */


//primes.c(hard)

//本Lab用到的SystemCall(很重要)
// int write(int fd, char *buf, int n)Write n bytes from buf to file descriptor fd; returns n.
// int read(int fd, char *buf, int n)Read n bytes into buf; returns number read; or 0 if end of file.
// int close(int fd)Release open file fd.
// int fork()Create a process, return child’s PID.
// int exit(int status)Terminate the current process; status reported to wait(). No return.
// int wait(int *status)Wait for a child to exit; exit status in *status; returns child PID.
// int pipe(int p[])Create a pipe, put read/write file descriptors in p[0] and p[1].

#include <kernel/types.h>
#include <kernel/stat.h>
#include <user/user.h>

//宏定义输入数组的大小，最终存储在数组中的数据是数组中对应下标+2
#define INPUT_NUM 34

//函数声明
void printPrimes(int *input,int num);


int main(){
    int input[INPUT_NUM];

    for(int i = 0;i < INPUT_NUM;i++){
        input[i] = i + 2;
    }
        
    printPrimes(input,INPUT_NUM);
    exit(0);
}

/**
 * @brief		a concurrent version of prime sieve using pipes
 * @details	    并发思想下的素数筛选器核心逻辑 
 * @param       input：输入数组名	
 * @param	    num：输入数组大小
 * @author      CalvinHaynes
 * @date        2021/7/14
 */
void printPrimes(int *input,int num){
    
    int p[2];       
    int prime = *input; //输入数组中的第一个数据赋值给prime

    if(num == 1){                   //迭代到num为1时就直接输出之后结束了
        printf("prime %d\n",prime);
        return;
    }

    printf("prime %d\n",prime);     //打印prime素数

    pipe(p);                       //创建管道

    if(fork() == 0){    //子线程一
        int temp1;

        for (int i = 0; i < num; i++){
            temp1 = *(input + i);           
            write(p[1],(char *)(&temp1),4); //循环写入input数组中的数据，注意write系统调用的参数
        }
        exit(0);
    }

    //极其重要，在这里遇到的天坑，所以审题尤其重要呜呜呜
    //在本Lab中的hints中有这么一条：Hint: read returns zero when the write-side of a pipe is closed.
    //这里的意思就是说只有当关闭pipe写端，即p[1]时，read才能在读到文件末尾时返回0
    //所以不关闭p[1]的后果可想而知：就是在子线程2中的代码中由于read永远不会返回0，所以卡在死循环中，导致结果只输出一个prime 2
    close(p[1]);                            


    if(fork() == 0){    //子线程2
        int temp2;
        int count = 0;                      //统计sieve筛选一次之后的prime个数
        char buffer[4];                     //用于读的buffer

        while(read(p[0],buffer,4) != 0){    //如果读到数据了进入循环，注意此前一定要关闭管道写端
            temp2 = *((int *)buffer);
            //prime是本次筛子sieve中所有数据的第一个数据，其实就是input数组的第一个数据，
            //可以把input数组意象化为筛子，所以input数组是随着筛子算法动态变化的       
            //temp2是存储读到buffer中的数据的临时变量
            if(temp2 % prime != 0){         
                *(input++) = temp2;         //筛掉不符合算法规则的数据，留下符合算法规则的数据以便于下次筛（下面的迭代）
                count++;
            }
        }

        printPrimes(input - count,count);   //迭代调用，继续筛，筛到count为1位置
        exit(0);
    }

    //为了线程安全，保证子线程的东西都执行完毕
    wait(0);
    wait(0);
}

//测试输出如下：

// $ primes
// prime 2
// prime 3
// prime 5
// prime 7
// prime 11
// prime 13
// prime 17
// prime 19
// prime 23
// prime 29
// prime 31
// $ 


// root@calvinhaynes-virtual-machine:~/xv6-labs-2020# ./grade-lab-util primes
// make: “kernel/kernel”已是最新。
// == Test primes == primes: OK (1.8s) 
