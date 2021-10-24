// 题目思路伪代码如下：
// p = get a number from left neighbor
// print p
// loop:
//     n = get a number from left neighbor
//     if (p does not divide n)
//         send n to right neighbor
#include<kernel/types.h>
#include<user/user.h>

#define PRIME_NUM 35
#define CHILD_PROCESS 0
#define NULL_INT (int *)0   
#define READ_END 0
#define WRITE_END 1

void child_process(int * p_left);

int main(){
    int p[2];
    pipe(p);

    if(fork() != CHILD_PROCESS){    //parent process
        //关掉pipe读端
        close(p[READ_END]);         

        //feed the numbers 2 through 35 into the pipeline
        for (int i = 2; i < PRIME_NUM + 1; i++)
        {
            write(p[WRITE_END],&i,sizeof(int));
        }

        //关闭pipe写端
        close(p[WRITE_END]);        
        //wait参数设置为NULL_INT表示不存储僵尸进程的死亡状态status，只是检测并杀死僵尸进程
        wait(NULL_INT);             
    } else{                         //child process
        child_process(p);
    }
    exit(0);
}

void child_process(int* pLeft){
    //存储管道中每一个number的中间变量
    int temp;           

    //读左管道的第一个数，如果为空，退出
    int readResult;
    close(pLeft[WRITE_END]);
    if((readResult = read(pLeft[READ_END],&temp,sizeof(int))) == 0)   
        exit(0);
    
    //创建右管道
    int pRight[2];
    pipe(pRight);   

    if(fork() != CHILD_PROCESS){        
        printf(" prime %d\n",temp);
        //将第一个输出的数存下来
        int prime = temp;   

        //读取所有左管道（前一管道的输入）的值和prime相除，整除则将对应的左管道中的值输出到右管道（输出到下一管道），循环往复
        while (read(pLeft[READ_END],&temp,sizeof(int)) != 0)
        {
            close(pRight[READ_END]);
            if (temp % prime != 0){
                write(pRight[WRITE_END],&temp,sizeof(int));
            }
        }

        close(pRight[WRITE_END]);
        wait(NULL_INT); 
    } else {
        child_process(pRight);      //递归迭代
    }
    exit(0);
}