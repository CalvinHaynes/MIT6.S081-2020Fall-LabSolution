//xargs命令的作用，是将标准输入转为命令行参数，默认情况下，xargs将换行符和空格作为分隔符，把标准输入分解成一个个命令行参数
#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"
#define MAX_ARG_LEN 100     //参数最大长度

int main(int argc, char *argv[]) {
	char *command = argv[1];                 //xars后第一个参数，即真实执行的命令的名字
	char temp;                               //读取标准输入临时存取标准输入值的临时变量
	char paramv[MAXARG][MAX_ARG_LEN];        //存参数的二维字符数组，每一行存一个参数，其中MAXARG是exec执行支持的最大参数数量（经历标准输入流参数和xargs后面参数的整合）
	char *m[MAXARG];                         //存最终要执行参数的字符指针数组，paramv二维数组中参数整合之后赋给此数组，作为exec系统调用的第二个参数最终执行
   
	while (1) {
        //作为之后读取标准输入中参数的基础指针（二维数组的行标，因为数组下标是从0开始的）
		int count = argc-1;  

		memset(paramv, 0, MAXARG * MAX_ARG_LEN);

		// 复制xargs之后的实际参数存到paramv二维数组中
		for (int i=1; i<argc; i++) {
			strcpy(paramv[i-1], argv[i]);
		}
   
		int cursor = 0;         // paramv二维数组每行的指针/游标（一位一位存参数时的游标）
		int flag = 0;           // 表明参数前空格的标志，flag=1说明还在读取参数，如果遇到空格/换行符就把flag置0，越过分隔符再读取到参数的时候就把flag置1
		int read_result;
   
		while (((read_result = read(0, &temp, 1))) > 0 && temp != '\n') {
            
            //空格分隔参数，过滤空格找到真正的参数，遇到空格就使paramv换行
			if (temp == ' ' && flag == 1) {
				count++;
				//在读取下一个参数之前将行的指针清零，并且把标志位置0
				cursor = 0;
				flag = 0;
			}
			else if (temp != ' ') {
				paramv[count][cursor++] = temp;
				flag = 1;
			}
		}

		// encounters EOF of input or \n
		if (read_result <= 0) {
			break;
		}

        //将拼接好的paramv数组（即包含标准输入中的参数和xargs后的参数）赋给字符指针数组m
		for (int i=0; i<MAXARG-1; i++) {
			m[i] = paramv[i];
		}
		m[MAXARG-1] = 0;

        //fork子进程执行xargs真实的可执行命令
		if (fork() == 0) {
			exec(command, m);
			exit(0);
		} else {
			wait((int *) 0);
		}
	}
	exit(0);
}