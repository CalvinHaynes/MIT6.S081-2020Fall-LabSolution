
/*
 * Copyright(c) 2021 Calvin Haynes
 * MIT Licensed
 * Project:MIT 6.S081
 */

//课堂例子，exercise一下
//copy input to output

#include"kernel/types.h"
#include"user/user.h"

int main(){
    char buff[64];

    while (1)
    {
        int n = read(0,buff,1+sizeof(buff));
        if(n <= 0)
            break;

        write(1,buff,n);
    }
    
    exit(0);
}

//输出结果：

// $ copy
// hello
// hello
// hi
// hi
// balabala
// balabala